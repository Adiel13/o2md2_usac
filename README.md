# O2MD²: ARM NEON Optimization and Performance Evaluation

**A research-oriented implementation and experimental evaluation of O2MD² on ARM Cortex-A72, including scalar, FFT, ARM NEON, and FFT+NEON variants.**

## Overview

This repository contains implementations of the O2MD² cryptographic scheme and experimental optimizations targeting ARM-based processors.

The primary objective is to investigate the impact of ARM NEON instructions and Fast Fourier Transform (FFT)-based polynomial arithmetic on the computational performance of O2MD².

The implementations were evaluated on a Raspberry Pi 4 equipped with an ARM Cortex-A72 processor, providing an experimental platform for studying cryptographic performance on resource-constrained computing systems.

The project focuses on three fundamental cryptographic operations:

- **Key Generation (KeyGen)**
- **Encryption (Encrypt)**
- **Decryption (Decrypt)**

Rather than assuming that SIMD acceleration always improves performance, this research examines performance differences across multiple implementations and parameter configurations.

## Implementation Variants

The repository contains 12 O2MD² implementations organized into three parameter configurations and four implementation strategies.

| Configuration | Scalar | FFT | NEON | FFT + NEON |
|---|---|---|---|---|
| OH6416 | OH6416 | OH6416FFT | OH6416NEON | OH6416FFTNEON |
| OH6432 | OH6432 | OH6432FFT | OH6432NEON | OH6432FFTNEON |
| OH6464 | OH6464 | OH6464FFT | OH6464NEON | OH6464FFTNEON |

### Implementation Strategies

**Scalar implementation**

The baseline implementation used as a reference for evaluating optimization strategies.

**FFT implementation**

An alternative implementation incorporating FFT-based polynomial arithmetic.

**ARM NEON implementation**

An implementation incorporating ARM NEON intrinsics to investigate instruction-level optimization opportunities on ARM processors.

**FFT + ARM NEON implementation**

A combined implementation that investigates the interaction between FFT-based polynomial arithmetic and ARM NEON instructions.

The presence of NEON intrinsics does not necessarily imply that every operation is vectorized or executed across multiple SIMD lanes.

## Experimental Platform

| Component | Description |
|---|---|
| Development board | Raspberry Pi 4 |
| Processor | ARM Cortex-A72 |
| Architecture | ARMv8-A, 64-bit capable |
| SIMD extension | ARM NEON / Advanced SIMD |
| Programming language | C |
| Cryptographic scheme | O2MD² |
| Evaluated operations | KeyGen, Encrypt, Decrypt |
| Experimental repetitions | 100 per evaluated configuration |

The exact compiler version, optimization flags, operating system, and processor configuration should be recorded when reproducing the experiments.

## Repository Structure

The O2MD² implementations are located under:

```text
c implementation/
└── CryptoAnalysis/
    ├── O2MD2/
    │   ├── OH6416/
    │   ├── OH6416FFT/
    │   ├── OH6416NEON/
    │   ├── OH6416FFTNEON/
    │   ├── OH6432/
    │   ├── OH6432FFT/
    │   ├── OH6432NEON/
    │   ├── OH6432FFTNEON/
    │   ├── OH6464/
    │   ├── OH6464FFT/
    │   ├── OH6464NEON/
    │   └── OH6464FFTNEON/
    ├── NIST/
    ├── Statistics/
    └── StatisticsMerger/
```

The `NIST` directory contains reference implementations used in the broader comparative evaluation, including variants of NTRU, NTRU Prime, FrodoKEM, CRYSTALS-Kyber, and ThreeBears.

These implementations correspond to different stages of the NIST post-quantum cryptography standardization process and should not all be interpreted as currently standardized algorithms.

## Getting Started

### 1. Clone the Repository

```bash
git clone https://github.com/Adiel13/o2md2_usac.git
cd o2md2_usac
```

### 2. Locate an Implementation

For example:

```bash
cd "c implementation/CryptoAnalysis/O2MD2/OH6416FFTNEON"
```

### 3. Compile

The repository contains C implementations, with Makefiles available in applicable directories.

Where a Makefile is provided, compilation can be attempted using:

```bash
make
```

Compilation procedures, dependencies, and target names may differ between implementation directories.

For ARM NEON experiments, use a compatible ARM toolchain and verify that the required instruction-set extensions are supported by the target processor.

### 4. Run Experiments

The experimental workflow evaluates the execution time of key generation, encryption, and decryption across the available implementations.

Users should inspect the corresponding implementation directory for its executable targets, test programs, and benchmark scripts.

Before reproducing the measurements, verify cryptographic correctness and ensure that all compared implementations use equivalent compiler optimization settings and experimental conditions.

## Performance Evaluation

The experimental analysis focuses on the execution-time differences
between scalar and optimized implementations.

For a baseline implementation with execution time
$T_{\text{baseline}}$ and an optimized implementation with execution
time $T_{\text{optimized}}$, speedup is defined as:

$$
S = \frac{T_{\text{baseline}}}{T_{\text{optimized}}}
$$

A value greater than 1 indicates an improvement, while a value
below 1 indicates a performance regression.

Percentage execution-time reduction is calculated as:

$$
R = \left(1-\frac{T_{\text{optimized}}}{T_{\text{baseline}}}\right)\times100
$$

The experiments investigate whether observed differences depend
on the parameter configuration, cryptographic operation, and
optimization strategy.

**Important:** ARM NEON acceleration does not guarantee a universal
performance improvement. Some implementations may exhibit regressions
due to additional computational overhead, data dependencies,
memory behavior, or the characteristics of the underlying arithmetic.
## Experimental Results

Benchmark results are stored in CSV files within the implementation directories and the `Statistics` directory.

These results support comparisons among:

- Baseline O2MD² implementations.
- FFT-based implementations.
- ARM NEON implementations.
- Combined FFT and ARM NEON implementations.
- Additional post-quantum cryptographic implementations included in the comparative dataset.

Reported results should distinguish between measured execution-time differences and claims of statistical significance.

## Reproducibility

To support reproducible research, experiments should document:

1. Hardware and processor specifications.
2. Operating system and compiler versions.
3. Compilation flags and optimization levels.
4. Number of experimental repetitions.
5. Measurement units and timing methodology.
6. Cryptographic correctness validation.
7. Statistical analysis procedures.

Reproductions should account for processor frequency scaling, background processes, thermal conditions, and other sources of experimental variability.

## Research Scope

This repository supports research into:

- Post-quantum cryptographic implementations.
- ARM processor optimization.
- SIMD and instruction-level acceleration.
- Polynomial arithmetic.
- FFT-based cryptographic computation.
- Embedded and resource-constrained computing.
- Experimental performance analysis and reproducibility.

The project is intended for research and experimental evaluation. The implementations should not be assumed to be production-ready or independently security-audited.

## Academic Citation

If you use this repository in academic work, please cite the associated research publication when available.

A versioned software release and archived DOI may be provided in the future to support persistent academic citation.

## Acknowledgments

This repository builds upon existing O2MD² implementation work and includes experimental modifications for ARM-based performance evaluation.

Original authorship, applicable licenses, and third-party implementation credits should be preserved in accordance with their respective source repositories and licensing terms.

## License

Please consult the repository's existing license files and the licenses associated with third-party cryptographic implementations.

No additional licensing permissions are implied by this README.

---

**Research area:** Post-Quantum Cryptography · ARM NEON · FFT · High-Performance Computing · Embedded Systems