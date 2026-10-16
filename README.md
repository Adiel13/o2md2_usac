# O2MD²: Hardware Optimization Using ARM NEON and FFT

**Research implementations and experimental performance evaluation of the O2MD² post-quantum cryptographic algorithm on ARM Cortex-A72 processors.**

## Overview

This repository contains the source code and experimental implementations associated with the doctoral dissertation **"Optimización por hardware del algoritmo criptográfico post-cuántico O2MD²"**, developed at Universidad Francisco Marroquín (UFM), Guatemala, in 2026.

The research investigates hardware-oriented optimization techniques for the O2MD² cryptographic algorithm, with particular emphasis on ARM NEON instructions and Fast Fourier Transform (FFT)-based polynomial arithmetic.

The implementations were evaluated on a Raspberry Pi 4 equipped with an ARM Cortex-A72 processor.

The principal objectives are to:

- Investigate the computational behavior of O2MD² on ARM processors.
- Evaluate the impact of ARM NEON instructions on cryptographic operations.
- Study FFT-based polynomial arithmetic and its interaction with NEON optimizations.
- Compare optimized implementations against their corresponding baseline versions.
- Provide experimental data for reproducible performance analysis.

The research evaluates three cryptographic operations: **Key Generation (KeyGen), Encryption (Encrypt), and Decryption (Decrypt)**.

## Implementation Variants

The repository contains 12 O2MD² implementations organized into three parameter configurations and four implementation strategies.

| Configuration | Baseline | FFT | NEON | FFT + NEON |
|---|---|---|---|---|
| OH6416 | OH6416 | OH6416FFT | OH6416NEON | OH6416FFTNEON |
| OH6432 | OH6432 | OH6432FFT | OH6432NEON | OH6432FFTNEON |
| OH6464 | OH6464 | OH6464FFT | OH6464NEON | OH6464FFTNEON |

### Baseline Implementations

The baseline implementations provide reference execution times for evaluating the optimization strategies.

### FFT Implementations

These variants investigate FFT-based approaches to polynomial arithmetic within the cryptographic implementation.

### ARM NEON Implementations

These variants incorporate ARM NEON intrinsics to investigate instruction-level optimization opportunities on ARM processors.

The use of NEON intrinsics does not necessarily imply that every operation achieves parallel execution across multiple SIMD lanes.

### FFT + ARM NEON Implementations

These variants combine FFT-based polynomial arithmetic with ARM NEON intrinsics to investigate the interaction between the two optimization strategies.

## Experimental Platform

| Component | Description |
|---|---|
| Development board | Raspberry Pi 4 |
| Processor | ARM Cortex-A72 |
| Architecture | ARMv8-A |
| SIMD technology | ARM NEON / Advanced SIMD |
| Programming language | C |
| Cryptographic algorithm | O2MD² |
| Evaluated operations | KeyGen, Encrypt, Decrypt |
| Experimental repetitions | 100 per evaluated configuration |

For rigorous reproduction, the operating system, compiler version, compilation flags, processor frequency, and measurement methodology should be documented alongside the experimental results.

## Repository Structure

```text
o2md2_usac/
|
+-- c implementation/
|   |
|   +-- CryptoAnalysis/
|       |
|       +-- O2MD2/
|       |   +-- OH6416/
|       |   +-- OH6416FFT/
|       |   +-- OH6416NEON/
|       |   +-- OH6416FFTNEON/
|       |   +-- OH6432/
|       |   +-- OH6432FFT/
|       |   +-- OH6432NEON/
|       |   +-- OH6432FFTNEON/
|       |   +-- OH6464/
|       |   +-- OH6464FFT/
|       |   +-- OH6464NEON/
|       |   +-- OH6464FFTNEON/
|       |
|       +-- NIST/
|       +-- Statistics/
|       +-- StatisticsMerger/
|
+-- README.md
```

The `O2MD2` directory contains the 12 implementation variants.

The `NIST` directory contains additional cryptographic implementations used for comparative evaluation, including variants from the NTRU, NTRU Prime, FrodoKEM, CRYSTALS-Kyber, and ThreeBears families.

These algorithms participated in different stages of the NIST post-quantum cryptography standardization process. Their inclusion does not imply that every implementation corresponds to a currently standardized algorithm.

The `Statistics` directory contains experimental results used in the comparative performance analysis.

## Getting Started

### Prerequisites

A compatible ARM development environment is recommended.

The project primarily uses C and includes implementation-specific build files.

Typical development tools include:

- GCC or another compatible C compiler.
- GNU Make.
- An ARM processor supporting the required instructions.
- Appropriate development libraries for the selected implementation.

Exact dependencies may vary between implementations.

### Clone the Repository

```bash
git clone https://github.com/Adiel13/o2md2_usac.git
cd o2md2_usac
```

### Select an Implementation

For example, to inspect the FFT + NEON implementation for OH6416:

```bash
cd "c implementation/CryptoAnalysis/O2MD2/OH6416FFTNEON"
```

### Compilation

Where an appropriate Makefile is available, compilation may be performed using:

```bash
make
```

Build targets and compiler requirements may differ between directories. Consult the implementation-specific Makefile before compilation.

The source code should be compiled with an appropriate ARM toolchain and compatible architecture settings.

### Execution and Validation

Before collecting benchmark results, verify that the selected implementation:

1. Compiles successfully.
2. Produces correct cryptographic outputs.
3. Passes the available correctness tests.
4. Uses the intended implementation and optimization settings.

Executable names and benchmark procedures depend on the selected implementation.

## Performance Evaluation

The experimental analysis focuses on execution-time differences between baseline and optimized implementations.

For a baseline implementation with execution time $T_{\text{baseline}}$ and an optimized implementation with execution time $T_{\text{optimized}}$, speedup is defined as:

$$
S = \frac{T_{\text{baseline}}}{T_{\text{optimized}}}
$$

A speedup greater than 1 indicates improved performance, whereas a value below 1 indicates a performance regression.

The percentage reduction in execution time is calculated as:

$$
R = \left(1-\frac{T_{\text{optimized}}}{T_{\text{baseline}}}\right)\times100
$$

Positive values indicate reduced execution time, while negative values indicate increased execution time.

### Evaluation Criteria

The experiments investigate performance differences according to:

- Cryptographic operation.
- Parameter configuration.
- Implementation strategy.
- Execution-time measurements.
- Relative performance improvement or regression.

**Important:** ARM NEON acceleration does not guarantee a universal performance improvement. Some implementations may exhibit regressions due to computational overhead, data dependencies, memory access patterns, or characteristics of the underlying arithmetic.

The presence of SIMD instructions alone is not sufficient evidence of an effective vectorized speedup.

## Experimental Results

The repository contains CSV files generated during the experimental evaluation.

These datasets support comparisons among the O2MD² implementation variants and the additional cryptographic implementations included in the study.

The analysis considers the execution times of KeyGen, Encrypt, and Decrypt.

Reported averages should be interpreted together with the experimental conditions and, where applicable, appropriate measures of variability and statistical uncertainty.

## Reproducibility

The repository is intended to support reproducible research in cryptographic performance optimization.

Researchers attempting to reproduce the experiments should document:

1. Hardware specifications and processor architecture.
2. Operating system and compiler versions.
3. Compiler flags and optimization settings.
4. Number of repetitions.
5. Timing units and measurement methodology.
6. Cryptographic correctness validation.
7. Processor frequency and thermal conditions.
8. Statistical analysis procedures.

Comparisons should use equivalent experimental conditions wherever possible.

Performance results obtained on other ARM processors or different compiler configurations may differ from those reported in the original experiments.

## Research Scope and Limitations

This repository supports research in:

- Post-quantum cryptography.
- ARM processor optimization.
- SIMD instruction-level acceleration.
- FFT-based polynomial arithmetic.
- Embedded computing.
- Cryptographic performance benchmarking.
- Experimental reproducibility.

The research focuses on computational performance rather than providing a new security proof for O2MD².

Performance improvements do not, by themselves, establish cryptographic security.

The implementations are provided as research artifacts and should not be assumed to be production-ready, independently security-audited, or suitable for protecting sensitive information without further validation.

## Academic Origin

This repository contains implementations developed and evaluated as part of the following doctoral dissertation:

**Optimización por hardware del algoritmo criptográfico post-cuántico O2MD²**

| Field | Information |
|---|---|
| Author | Kevin Adiel Lajpop Ajpacajá |
| Academic institution | Universidad Francisco Marroquín (UFM) |
| Country | Guatemala |
| Doctoral program | Doctorado en Ciencias de la Computación |
| Year | 2026 |
| Doctoral advisor | Dr. Ricardo Neftalí Pontaza Rodas |

The doctoral research investigates hardware-oriented optimization techniques for O2MD², particularly ARM NEON instructions and FFT-based implementations.

The original cryptographic design and the doctoral optimization contributions are acknowledged separately.

The repository is intended to support the dissemination and reproducibility of the associated academic research, subject to applicable intellectual property rights and distribution permissions.

## Acknowledgments

The O2MD² cryptographic scheme was originally developed by **Ricardo Neftalí Pontaza Rodas and Ying-Dar Lin**.

The author acknowledges the academic guidance of Dr. Ricardo Neftalí Pontaza Rodas during the doctoral research conducted at Universidad Francisco Marroquín.

The repository also contains third-party cryptographic implementations used for comparative experimental analysis. Their original authorship and applicable licensing conditions remain with their respective contributors and rights holders.

## Intellectual Property and Patent Notice

O2MD² is associated with a family of patent documents covering aspects of the original cryptographic technology.

The following documents have been identified:

| Jurisdiction | Patent or Publication | Document Type |
|---|---|---|
| United States | [US11218308B2](https://patents.google.com/patent/US11218308B2/en) | Granted patent |
| China | [CN110958112B](https://patents.google.com/patent/CN110958112B/en) | Granted patent |
| Taiwan | [TWI672932B](https://patents.google.com/patent/TWI672932B/en) | Granted patent |
| Japan | [JP7053537B6](https://patents.google.com/patent/JP7053537B6/en) | Granted patent; corrected publication |
| Europe | [EP3629517A1](https://patents.google.com/patent/EP3629517A1/en) | Published patent application |
| South Korea | [KR102354456B1](https://patents.google.com/patent/KR102354456B1/en) | Granted patent |
| Japan | [JP2022059057A](https://patents.google.com/patent/JP2022059057A/en) | Published divisional application |

**Named inventors:**

- Ricardo Neftalí Pontaza Rodas.
- Ying-Dar Lin.

The listed documents are related to the original cryptographic technology. They do not necessarily represent seven independent inventions.

Patent publication and grant information should not be interpreted as confirmation of current enforceability, ownership, or legal status in every jurisdiction.

### Relationship to the Present Research

The original O2MD² cryptographic design is distinguished from the hardware optimization and experimental evaluation conducted as part of the doctoral research.

The presence of ARM NEON or FFT-related modifications does not, by itself, establish freedom to operate under the original patents.

### Patent Rights Disclaimer

**The public availability of this repository does not, by itself, grant a patent license or authorization to commercially exploit the patented cryptographic technology.**

Any permissions to use, reproduce, modify, distribute, or commercialize the implementations must be determined from the applicable copyright licenses, patent rights, and authorizations from the relevant rights holders.

This notice is provided for academic attribution and informational purposes and does not constitute legal advice.

## Software Licensing

The repository contains original research contributions as well as implementations derived from or associated with existing cryptographic software.

Licensing and distribution permissions must be verified for the respective components.

No repository-wide open-source license is declared by this README.

Users should consult the applicable source files, third-party licenses, and rights holders before redistributing or commercially using the software.

## Citation

If you use this repository in academic work, please acknowledge the doctoral research and the original O2MD² cryptographic design.

**Doctoral dissertation:**

Lajpop Ajpacajá, K. A. (2026). *Optimización por hardware del algoritmo criptográfico post-cuántico O2MD²*. Doctoral dissertation, Universidad Francisco Marroquín, Guatemala.

A persistent identifier and formal software citation may be added following the release and archival of an authorized, versioned research artifact.

## Repository

**GitHub:** https://github.com/Adiel13/o2md2_usac

---

**Keywords:** Post-Quantum Cryptography · O2MD² · ARM NEON · ARM Cortex-A72 · FFT · Hardware Optimization · Raspberry Pi 4 · Cryptographic Benchmarking · Reproducible Research