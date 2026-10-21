# RSOS-262526 — Statistical reproducibility package

## Associated manuscript

**Kevin Lajpop Ajpacajá.** *Beyond Average Speedup: A Statistical Evaluation of FFT and ARM NEON Optimizations for O2MD² on Cortex-A72*. Submitted to **Royal Society Open Science**, manuscript **RSOS-262526**. This package documents statistical processing of the benchmark CSV files; it is not a substitute for the original benchmark executables or an independent security audit.

## Contents

```text
rsos_analysis/
├── analyze.py
├── requirements.txt
├── README.md
├── data/                    # 12 individual benchmark CSV files
│   └── totalStatistics-O2MD2-<VARIANT>.csv
└── results/                 # Generated when analyze.py runs
    ├── measurements_long.csv
    ├── descriptive_statistics.csv
    ├── comparisons_36.csv
    ├── figure1_distributions.png
    ├── figure2_slowdown.png
    ├── figure3_mean_median.png
    ├── figure4_extreme_cases.png
    └── figure5_bootstrap.png
```

## Requirements and execution

Use **Python 3.10 or later** with NumPy, pandas, SciPy, Matplotlib, and statsmodels. The `requirements.txt` file specifies minimum versions rather than a fully locked environment; record exact installed versions if byte-for-byte reproduction is needed.

From the `rsos_analysis/` directory:

```bash
python -m venv .venv
source .venv/bin/activate  # Windows PowerShell: .venv\Scripts\Activate.ps1
python -m pip install -r requirements.txt
python analyze.py
```

The script also accepts `--data`, `--output`, `--seed`, and `--bootstrap` arguments. Defaults: `data/`, `results/`, **20261017**, and **30000**, respectively. Do not change the defaults when attempting to reproduce the manuscript's stated methodology.

## Input dataset and validation

The input consists of 12 separate CSV files: three configurations (`OH6416`, `OH6432`, `OH6464`) × four implementation labels (Baseline, FFT, NEON, FFT+NEON). Each contains `case No.`, `KeyGen(ns)`, `Encrypt(ns)`, and `Decrypt(ns)`. The script checks 100 cases indexed 0–99, positive finite timings, and the expected file naming pattern. All **3,600** recorded timings are retained; outliers are **not** removed. The separately consolidated benchmark file is intentionally excluded, as described in manuscript §4(b).

The case number is a record index, **not evidence of pairing** between variants. The script treats groups as independent for its exploratory resampling and tests, an assumption that cannot be verified from the CSVs alone.

## Statistical methods

For each of the **36 groups** (12 variants × 3 operations), the script exports sample size, mean, median, sample standard deviation, Q1, Q3, IQR, 10% trimmed mean, minimum, and maximum. Times are stored in **nanoseconds**; plotted figures convert to **microseconds** where indicated.

For each of the **9 configuration–operation combinations**, it calculates four contrasts: Baseline → FFT; Baseline → NEON; FFT → FFT+NEON; Baseline → FFT+NEON, yielding **36 contrasts**. Percentage reductions are calculated as `100 * (1 - comparison/reference)` separately for group means, medians, and trimmed means; positive values indicate faster comparison variants.

Mean- and median-based 95% **percentile bootstrap** intervals use **30,000** within-group resamples with replacement and random seed **20261017**. Two-sided **Welch unequal-variance t-tests** are run for the 36 contrasts and their p-values jointly adjusted by the **Holm** procedure; adjusted p-values below 0.05 are marked as exploratory. Bootstrap intervals are not multiplicity-adjusted.

## Mapping outputs to the manuscript

| Output | Use in the manuscript |
|---|---|
| `descriptive_statistics.csv` | §4(c), §5(a); Table 2 medians (convert ns to µs) and variability summaries |
| `comparisons_36.csv` | §4(c–d), §5(b–e); Table 3 mean/median reductions, bootstrap intervals, Welch/Holm results |
| `figure1_distributions.png` | Figure 1: distributions by configuration and operation (log scale) |
| `figure2_slowdown.png` | Figure 2: FFT-based median slowdown factors vs baseline |
| `figure3_mean_median.png` | Figure 3: mean-based vs median-based percentage reductions |
| `figure4_extreme_cases.png` | Figure 4: four selected case-index traces and extreme observations |
| `figure5_bootstrap.png` | Figure 5: bootstrap intervals for the 18 primary contrasts |

Figures are **reconstructions of the analytical content**, not necessarily pixel-identical to the submitted manuscript. The exact RNG implementation and draw order used in the original analysis were not archived; bootstrap endpoints may differ slightly despite matching seed and resample count.

## Checks and interpretation

The reconstructed analysis was previously checked against selected manuscript figures and numerical results, including the mean-based OH6416 FFT → FFT+NEON encryption reduction (approximately **13.8%**), OH6432 FFT → FFT+NEON encryption (approximately **−30.1%**), and the reported **23/36** Holm-significant contrasts. These spot checks are **not** a full audit of every table cell or plotted interval. Run the code in your environment and compare generated outputs against the final submitted PDF before archival release.

## Provenance and limitations

**The Python analysis script was reconstructed after manuscript submission.** It implements the procedures described in manuscript §4, but should not be described as the original contemporaneous analysis code. This package supports reproduction of **statistical processing of the recorded data**, not reproduction of the original Raspberry Pi 4 timing acquisition. Original measurement replication requires exact source revisions and executables, compiler and OS versions, CPU and thermal settings, measurement instrumentation, execution order, input policy, and functional-equivalence checks. None should be inferred from the timing CSVs alone.

The repository's current twelve implementation directories do not by themselves establish a one-to-one provenance mapping to the measured binaries. Licensing and third-party redistribution permissions are addressed separately in [`../INTELLECTUAL_PROPERTY.md`](../INTELLECTUAL_PROPERTY.md).

## Citation and archival status

Cite the associated manuscript and, **once an archival release is deposited**, cite the repository version using its actual DOI. **No DOI is asserted in this README.**
