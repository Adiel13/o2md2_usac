#!/usr/bin/env python3
"""Reconstruct statistical processing specified in RSOS-262526, section 4."""
from pathlib import Path
import argparse
import numpy as np
import pandas as pd
from scipy import stats
from statsmodels.stats.multitest import multipletests
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

CONFIGS=['OH6416','OH6432','OH6464']
OPS={'KeyGen':'KeyGen(ns)','Encrypt':'Encrypt(ns)','Decrypt':'Decrypt(ns)'}
VARIANTS={'Baseline':'','FFT':'FFT','NEON':'NEON','FFT+NEON':'FFTNEON'}
PAIRS=[('Baseline','FFT'),('Baseline','NEON'),('FFT','FFT+NEON'),('Baseline','FFT+NEON')]

def reduction(a,b): return 100*(1-b/a)
def main(data,out,seed=20261017,bootstrap=30000):
    out.mkdir(parents=True,exist_ok=True)
    rng=np.random.default_rng(seed)
    groups={}; rows=[]; desc=[]
    for config in CONFIGS:
        for variant,suffix in VARIANTS.items():
            f=data/f'totalStatistics-O2MD2-{config}{suffix}.csv'
            df=pd.read_csv(f)
            assert len(df)==100 and df['case No.'].tolist()==list(range(100)),f
            for op,col in OPS.items():
                x=pd.to_numeric(df[col],errors='raise').to_numpy(float)
                assert np.isfinite(x).all() and (x>0).all()
                groups[config,variant,op]=x
                rows.extend(dict(configuration=config,variant=variant,operation=op,case_no=int(i),time_ns=v) for i,v in zip(df['case No.'],x))
                desc.append(dict(configuration=config,variant=variant,operation=op,n=100,mean_ns=x.mean(),median_ns=np.median(x),sd_ns=x.std(ddof=1),q1_ns=np.quantile(x,.25),q3_ns=np.quantile(x,.75),iqr_ns=np.quantile(x,.75)-np.quantile(x,.25),trimmed_mean_10_ns=stats.trim_mean(x,.1),min_ns=x.min(),max_ns=x.max()))
    pd.DataFrame(rows).to_csv(out/'measurements_long.csv',index=False)
    pd.DataFrame(desc).to_csv(out/'descriptive_statistics.csv',index=False)
    comparisons=[]
    for config in CONFIGS:
        for op in OPS:
            for a,b in PAIRS:
                x,y=groups[config,a,op],groups[config,b,op]
                # independent within-group bootstrap, no trial pairing
                xb=x[rng.integers(len(x),size=(bootstrap,len(x)))]; yb=y[rng.integers(len(y),size=(bootstrap,len(y)))]
                bm=reduction(xb.mean(axis=1),yb.mean(axis=1))
                bmed=reduction(np.median(xb,axis=1),np.median(yb,axis=1))
                p=stats.ttest_ind(x,y,equal_var=False).pvalue
                comparisons.append(dict(configuration=config,operation=op,reference=a,comparison=b,mean_reduction_pct=reduction(x.mean(),y.mean()),median_reduction_pct=reduction(np.median(x),np.median(y)),trimmed_mean_reduction_pct=reduction(stats.trim_mean(x,.1),stats.trim_mean(y,.1)),mean_ci_low_pct=np.quantile(bm,.025),mean_ci_high_pct=np.quantile(bm,.975),median_ci_low_pct=np.quantile(bmed,.025),median_ci_high_pct=np.quantile(bmed,.975),welch_p=p))
    comp=pd.DataFrame(comparisons)
    comp['holm_p']=multipletests(comp.welch_p,method='holm')[1]
    comp['holm_significant_05']=comp.holm_p<.05
    comp.to_csv(out/'comparisons_36.csv',index=False)
    # Figure 1: distribution panels
    fig,axes=plt.subplots(3,3,figsize=(13,11))
    for i,c in enumerate(CONFIGS):
        for j,o in enumerate(OPS):
            xs=[groups[c,v,o]/1000 for v in VARIANTS]
            ax=axes[i,j];ax.boxplot(xs,showmeans=True,meanprops=dict(marker='D',markerfacecolor='white',markeredgecolor='black'),flierprops=dict(marker='.',markersize=3));ax.set_yscale('log');ax.set_xticks(range(1,5),list(VARIANTS),rotation=30);ax.set_title(f'{c} / {o}');ax.set_ylabel('Time (µs, log)')
    fig.tight_layout();fig.savefig(out/'figure1_distributions.png',dpi=180);plt.close(fig)
    # Figure 2: median slowdown
    fig,axes=plt.subplots(1,3,figsize=(13,4))
    for i,c in enumerate(CONFIGS):
        ax=axes[i]; xx=np.arange(3)
        for shift,v in [(-.18,'FFT'),(.18,'FFT+NEON')]:
            yy=[np.median(groups[c,v,o])/np.median(groups[c,'Baseline',o]) for o in OPS]
            ax.bar(xx+shift,yy,width=.36,label=v)
        ax.set_xticks(xx,list(OPS));ax.set_title(c);ax.set_ylabel('Median slowdown (×)');ax.legend()
    fig.tight_layout();fig.savefig(out/'figure2_slowdown.png',dpi=180);plt.close(fig)
    # Figure 3: reductions heatmap
    fig,axes=plt.subplots(2,2,figsize=(12,7))
    for i,(a,b) in enumerate([('Baseline','NEON'),('FFT','FFT+NEON')]):
        for j,(col,title) in enumerate([('mean_reduction_pct','Mean'),('median_reduction_pct','Median')]):
            matrix=np.array([[comp[(comp.configuration==c)&(comp.operation==o)&(comp.reference==a)&(comp.comparison==b)].iloc[0][col] for o in OPS] for c in CONFIGS]); ax=axes[i,j];im=ax.imshow(matrix,vmin=-70,vmax=70,cmap='coolwarm_r');ax.set_xticks(range(3),list(OPS));ax.set_yticks(range(3),CONFIGS);ax.set_title(f'{a} → {b}: {title}');
            for r in range(3):
                for k in range(3): ax.text(k,r,f'{matrix[r,k]:+.1f}%',ha='center',va='center',fontsize=9)
    fig.colorbar(im,ax=axes.ravel().tolist(),shrink=.65,label='Reduction (%)');fig.subplots_adjust(right=.88,hspace=.4,wspace=.3);fig.savefig(out/'figure3_mean_median.png',dpi=180);plt.close(fig)
    # Figure 4: case traces
    selected=[('OH6432','Baseline','Encrypt'),('OH6432','Baseline','Decrypt'),('OH6464','NEON','KeyGen'),('OH6464','FFT+NEON','KeyGen')]
    fig,axes=plt.subplots(2,2,figsize=(11,7))
    for ax,(c,v,o) in zip(axes.ravel(),selected):
        x=groups[c,v,o]/1000;ax.scatter(np.arange(100),x,s=9);ax.axhline(np.median(x),linestyle='--',color='gray');ax.set_yscale('log');ax.set_title(f'{c} / {v} / {o}');ax.set_xlabel('Case number');ax.set_ylabel('Time (µs)')
    fig.tight_layout();fig.savefig(out/'figure4_extreme_cases.png',dpi=180);plt.close(fig)
    # Figure 5: mean and median bootstrap intervals for primary comparisons
    fig,axes=plt.subplots(1,2,figsize=(13,8),sharey=True)
    for ax,(a,b) in zip(axes,[('Baseline','NEON'),('FFT','FFT+NEON')]):
        subset=comp[(comp.reference==a)&(comp.comparison==b)].reset_index(drop=True)
        for k,r in subset.iterrows():
            for offset,estimate,lo,hi,marker in [(-.13,'mean_reduction_pct','mean_ci_low_pct','mean_ci_high_pct','o'),(.13,'median_reduction_pct','median_ci_low_pct','median_ci_high_pct','s')]:
                ax.errorbar(r[estimate],k+offset,xerr=[[r[estimate]-r[lo]],[r[hi]-r[estimate]]],fmt=marker,capsize=2,markersize=4)
        ax.axvline(0,linestyle='--',color='gray');ax.set_title(f'{a} → {b}');ax.set_xlabel('Reduction (%)');ax.set_yticks(range(9),[f'{r.configuration} / {r.operation}' for r in subset.itertuples()]);ax.invert_yaxis()
    fig.tight_layout();fig.savefig(out/'figure5_bootstrap.png',dpi=180);plt.close(fig)
    print(f'{len(rows)} observations, {len(desc)} groups, {len(comp)} contrasts, Holm significant: {comp.holm_significant_05.sum()}')
    for c,o,a,b in [('OH6416','Encrypt','FFT','FFT+NEON'),('OH6432','Encrypt','FFT','FFT+NEON'),('OH6432','Encrypt','Baseline','NEON')]:
        r=comp[(comp.configuration==c)&(comp.operation==o)&(comp.reference==a)&(comp.comparison==b)].iloc[0]
        print(c,o,a,b,'mean',round(r.mean_reduction_pct,2),'CI',round(r.mean_ci_low_pct,2),round(r.mean_ci_high_pct,2))
if __name__=='__main__':
    p=argparse.ArgumentParser();p.add_argument('--data',type=Path,default=Path(__file__).parent/'data');p.add_argument('--output',type=Path,default=Path(__file__).parent/'results');p.add_argument('--seed',type=int,default=20261017);p.add_argument('--bootstrap',type=int,default=30000);a=p.parse_args();main(a.data,a.output,a.seed,a.bootstrap)
