# O2MD²: Hardware Optimization Using ARM NEON and FFT

**Hardware-oriented optimization and experimental performance evaluation of the O2MD² post-quantum cryptographic algorithm on ARM Cortex-A72 processors.**

[![Research](https://img.shields.io/badge/Research-Post--Quantum%20Cryptography-blue)](https://github.com/Adiel13/o2md2_usac)

[![Architecture](https://img.shields.io/badge/Architecture-ARM%20Cortex--A72-green)](https://github.com/Adiel13/o2md2_usac)

[![Platform](https://img.shields.io/badge/Platform-Raspberry%20Pi%204-red)](https://github.com/Adiel13/o2md2_usac)

[![Language](https://img.shields.io/badge/Language-C-orange)](https://github.com/Adiel13/o2md2_usac)

## Overview

This repository contains research implementations and experimental materials associated with the doctoral dissertation:

**"Optimización por hardware del algoritmo criptográfico post-cuántico O2MD²"**

The research was conducted by **Kevin Adiel Lajpop Ajpacajá** at Universidad Francisco Marroquín (UFM), Guatemala, under the supervision of **Dr. Ricardo Neftalí Pontaza Rodas**, in 2026.

The project investigates hardware-oriented optimization strategies for the O2MD² cryptographic algorithm, focusing on ARM NEON instructions and Fast Fourier Transform (FFT)-based polynomial arithmetic.

The experimental platform is a Raspberry Pi 4 equipped with an ARM Cortex-A72 processor.

The principal research objectives are:

- Investigate the computational performance of O2MD² on ARM processors.

- Evaluate ARM NEON optimization strategies for cryptographic operations.

- Analyze FFT-based polynomial arithmetic and its computational characteristics.

- Compare baseline, FFT, NEON, and FFT+NEON implementations.

- Identify performance improvements and regressions across parameter configurations.

- Support reproducible experimental evaluation of post-quantum cryptographic implementations.

The experiments consider three cryptographic operations:

**Key Generation (KeyGen), Encryption (Encrypt), and Decryption (Decrypt).**

## Implementation Variants

The repository contains **12 O2MD² implementation variants**, organized into three parameter configurations and four implementation strategies.

| Configuration | Baseline | FFT | NEON | FFT + NEON |
|---|---|---|---|---|
| OH6416 | OH6416 | OH6416FFT | OH6416NEON | OH6416FFTNEON |
| OH6432 | OH6432 | OH6432FFT | OH6432NEON | OH6432FFTNEON |
| OH6464 | OH6464 | OH6464FFT | OH6464NEON | OH6464FFTNEON |

### Baseline Implementations

The baseline implementations serve as reference configurations for evaluating the performance of the optimized variants.

### FFT Implementations

The FFT variants investigate polynomial arithmetic based on the Fast Fourier Transform.

Their objective is to study the computational behavior of FFT-based operations within O2MD².

### ARM NEON Implementations

The NEON variants incorporate ARM Advanced SIMD intrinsics to investigate hardware-oriented acceleration opportunities.

ARM NEON provides vector instructions capable of operating on multiple data elements under suitable conditions.

However, the presence of NEON intrinsics does not necessarily imply that every operation is effectively vectorized or that every instruction processes multiple independent elements.

### FFT + ARM NEON Implementations

The combined implementations investigate the interaction between FFT-based polynomial arithmetic and ARM NEON instructions.

These variants are evaluated independently because combining optimization techniques does not necessarily produce cumulative performance improvements.

## Experimental Platform

| Component | Description |
|---|---|
| Development board | Raspberry Pi 4 |
| Processor | ARM Cortex-A72 |
| Instruction set | ARMv8-A |
| SIMD extension | ARM NEON / Advanced SIMD |
| Programming language | C |
| Cryptographic scheme | O2MD² |
| Evaluated operations | KeyGen, Encrypt, Decrypt |
| Experimental repetitions | 100 per evaluated configuration |

The Raspberry Pi 4 provides an ARM-based experimental environment for evaluating cryptographic implementations on resource-constrained computing platforms.

Compiler versions, optimization flags, operating system configuration, processor frequency, and thermal conditions may affect the results.

## Repository Structure

The research implementations are organized under `c implementation/CryptoAnalysis/`.

```text

o2md2_usac/

│

├── c implementation/

│   └── CryptoAnalysis/

│       │

│       ├── O2MD2/

│       │   ├── OH6416/

│       │   ├── OH6416FFT/

│       │   ├── OH6416NEON/

│       │   ├── OH6416FFTNEON/

│       │   │

│       │   ├── OH6432/

│       │   ├── OH6432FFT/

│       │   ├── OH6432NEON/

│       │   ├── OH6432FFTNEON/

│       │   │

│       │   ├── OH6464/

│       │   ├── OH6464FFT/

│       │   ├── OH6464NEON/

│       │   └── OH6464FFTNEON/

│       │

│       ├── NIST/

│       ├── Statistics/

│       └── StatisticsMerger/

│

└── README.md

```

### O2MD2

Contains the baseline and optimized implementations of the O2MD² cryptographic algorithm.

### NIST

Contains additional post-quantum cryptographic implementations used in the comparative evaluation, including variants of:

- NTRU

- NTRU Prime

- FrodoKEM

- CRYSTALS-Kyber

- ThreeBears

These implementations correspond to different stages of the NIST post-quantum cryptography standardization process.

Their inclusion does not imply that all listed algorithms or variants are currently standardized by NIST.

### Statistics

Contains experimental data used for performance evaluation.

### StatisticsMerger

Contains materials associated with aggregating experimental results.

## Getting Started

### Prerequisites

A compatible ARM development environment is recommended.

Typical development tools include:

- GCC or another compatible C compiler.

- GNU Make.

- An ARM processor supporting the required instruction set.

- Implementation-specific development dependencies.

Exact dependencies and build requirements may vary across directories.

### Clone the Repository

```bash

git clone https://github.com/Adiel13/o2md2_usac.git

cd o2md2_usac

```

### Select an Implementation

For example, to inspect the OH6416 FFT+NEON variant:

```bash

cd "c implementation/CryptoAnalysis/O2MD2/OH6416FFTNEON"

```

### Compilation

Where a suitable Makefile is available, compilation can be attempted using:

```bash

make

```

Build targets, compiler options, and dependencies may vary between implementation directories.

Researchers should inspect the corresponding Makefile and source files before compiling.

### Execution

Each implementation should be validated before performance measurements are collected.

The recommended procedure is to:

1. Compile the selected implementation.

2. Execute the available cryptographic correctness tests.

3. Verify successful key generation, encryption, and decryption.

4. Execute the appropriate benchmark programs or scripts.

5. Record execution-time measurements.

6. Export and analyze the experimental results.

Executable names and benchmark commands are implementation-specific and should be verified in the corresponding source directory.

## Performance Evaluation

The experimental analysis focuses on execution-time differences between baseline and optimized implementations.

### Speedup

For a baseline implementation with execution time $T_{\text{baseline}}$ and an optimized implementation with execution time $T_{\text{optimized}}$, speedup is defined as:

```math
S = \frac{T_{\text{baseline}}}{T_{\text{optimized}}}
```

Where:

- $S > 1$: Performance improvement.

- $S = 1$: Equivalent execution time.

- $S < 1$: Performance regression.

### Execution-Time Reduction

The percentage reduction in execution time is calculated as:

```math
R = \left(1-\frac{T_{\text{optimized}}}{T_{\text{baseline}}}\right)\times100
```

Positive values indicate reduced execution time, whereas negative values indicate increased execution time.

### Evaluation Dimensions

The experimental evaluation considers:

- Parameter configuration.

- Cryptographic operation.

- Optimization strategy.

- Execution-time measurements.

- Relative performance improvements.

- Performance regressions.

- Statistical variability.

### Interpretation

**ARM NEON acceleration does not guarantee universal performance improvements.**

The effectiveness of an optimization depends on the implementation, arithmetic operations, data dependencies, memory access patterns, compiler behavior, and characteristics of the target architecture.

Consequently, FFT-based and NEON-based implementations are evaluated independently rather than assuming that optimization techniques always produce positive speedups.

## Experimental Results

The repository contains CSV files generated during the experimental evaluation.

These datasets support comparisons between the 12 O2MD² variants and additional post-quantum cryptographic implementations included in the research.

The experiments examine execution-time measurements for KeyGen, Encrypt, and Decrypt.

Results should be interpreted in relation to the specific hardware, software environment, and measurement methodology used.

Average execution times alone do not establish statistical significance. Where appropriate, variability and uncertainty should also be considered.

## Reproducibility

This repository is intended to support reproducible research in cryptographic performance optimization.

Researchers attempting to reproduce the experiments should document:

1. Processor and hardware specifications.

2. Operating system version.

3. Compiler version.

4. Compilation and optimization flags.

5. Number of experimental repetitions.

6. Timing methodology and measurement units.

7. Cryptographic correctness validation.

8. Processor frequency and thermal conditions.

9. Background system activity.

10. Statistical analysis methodology.

Comparisons should be performed under equivalent experimental conditions wherever possible.

Results obtained on other ARM processors or with different compiler configurations may differ from those observed on the Raspberry Pi 4.

## Research Scope and Limitations

This repository supports research into:

- Post-quantum cryptography.

- ARM processor optimization.

- SIMD and instruction-level acceleration.

- FFT-based polynomial arithmetic.

- Embedded and resource-constrained computing.

- Cryptographic benchmarking.

- Experimental performance analysis.

- Reproducible computational research.

The research focuses on computational performance and hardware-oriented optimization.

It does not establish a new cryptographic security proof for O2MD².

Performance improvements do not imply resistance to cryptanalysis, side-channel attacks, or quantum adversaries.

The implementations are research artifacts and should not be assumed to be production-ready or independently security-audited.

## Academic Origin

This repository contains the research implementations used in the doctoral dissertation:

**Optimización por hardware del algoritmo criptográfico post-cuántico O2MD²**

| Field | Information |
|---|---|
| Doctoral researcher | Kevin Adiel Lajpop Ajpacajá |
| Institution | Universidad Francisco Marroquín (UFM) |
| Doctoral program | Doctorado en Ciencias de la Computación |
| Country | Guatemala |
| Year | 2026 |
| Doctoral advisor | Dr. Ricardo Neftalí Pontaza Rodas |

The doctoral research investigates hardware-oriented optimization strategies for the O2MD² cryptographic algorithm.

The research contributions include ARM NEON implementations, FFT-based variants, and experimental performance evaluation on ARM Cortex-A72 processors.

The original cryptographic design and the doctoral optimization contributions are acknowledged separately.

## Acknowledgments

The O2MD² cryptographic scheme was originally developed by:

- **Dr. Ricardo Neftalí Pontaza Rodas**

- **Dr. Ying-Dar Lin**

The doctoral researcher acknowledges the academic guidance of Dr. Ricardo Neftalí Pontaza Rodas during the research conducted at Universidad Francisco Marroquín.

The repository also includes third-party post-quantum cryptographic implementations used for comparative evaluation.

Original authorship, copyright notices, and applicable licenses remain associated with their respective components and rights holders.

## Royal Society Open Science — Statistical Reproducibility

The reproducibility materials for the submitted manuscript **“Beyond Average Speedup: A Statistical Evaluation of FFT and ARM NEON Optimizations for O2MD² on Cortex-A72”** (Royal Society Open Science, manuscript **RSOS-262526**) are documented in [`rsos_analysis/README.md`](rsos_analysis/README.md).

The analysis uses twelve individual CSV files (100 cases × 3 operations × 12 implementation labels = **3,600 execution-time observations**) and produces descriptive statistics, 36 pairwise contrasts, 30,000-resample percentile-bootstrap confidence intervals, two-sided Welch tests with Holm correction, and reconstructions of Figures 1–5.

**Reproducibility boundary:** The reconstructed Python scripts permit reanalysis of the recorded timing data; they do **not** independently establish which source revision or executable generated each CSV, whether the implementation variants are functionally equivalent, or the original benchmark environment. The submitted manuscript discusses an earlier inspected six-directory source snapshot; the current repository lists twelve variant directories. Their correspondence to the measured executables remains to be verified.

The analysis scripts were reconstructed after manuscript submission, and the figure renderings may differ visually from the submitted figures. A persistent archival DOI has **not yet been assigned**.

## Intellectual Property and Licensing

The original O2MD² cryptographic technology is associated with patent filings, and this repository also contains third-party software. Public access to source code does not itself grant patent rights or establish a repository-wide software license.

See [Intellectual Property and Licensing](INTELLECTUAL_PROPERTY.md) for inventor attribution, patent references, reported status information, and redistribution considerations. **Rights and permissions must be verified before republishing source code in another archive.**

## Citation

If you use this repository in academic work, please acknowledge the doctoral dissertation and the original O2MD² cryptographic design.

### Doctoral Dissertation

Lajpop Ajpacajá, K. A. (2026). **Optimización por hardware del algoritmo criptográfico post-cuántico O2MD²**. Doctoral dissertation, Universidad Francisco Marroquín, Guatemala.

### Software Repository

Lajpop Ajpacajá, K. A. (2026). **O2MD²: Hardware Optimization Using ARM NEON and FFT**. Research software repository.

https://github.com/Adiel13/o2md2_usac

A versioned software release and persistent DOI may be added after the applicable distribution permissions and reproducibility requirements have been verified.

## Repository

**GitHub:** https://github.com/Adiel13/o2md2_usac

---

**Keywords:** Post-Quantum Cryptography · O2MD² · ARM NEON · ARM Cortex-A72 · FFT · Hardware Optimization · Raspberry Pi 4 · Cryptographic Benchmarking · Reproducible Research
