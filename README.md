# arithmetic-coding

This repository contains the code for the published work [*Comprehensive Analysis of Software-Based Fault Tolerance with Arithmetic Coding for Performant Encoding of Integer Calculations*](https://doi.org/10.1007/978-3-031-14835-4_10) at *SAFECOMP2022*

## Requirements
For an accurate performance measurement we use an Linux with PREEMPT_RT. Furthermore, the rtPerfLog library is used for the measurements. This lib is added as submodule and must be updated after cloning.
```bash
git submodule init
git submodule update
```

## How to build
CMAKE required. Exeute `./build.sh` to build all binaries and dependencies.

## Structure of the repository
- **codings** Contains the encoded operations for each encoding.
- **mul_validation** Code for the validation with a matrix multiplication.
- **plots** Some python files to generate the plots in the paper.
- **results** Output of the metric evalutation and fault simulation.
- **rtPerfLog** Submodule of rtPerfLog library
- **src** The source files for the metric evaluation, fault simulation, and performance analysis.
- **build.sh** Script to build all binaries
- **execute-detcap.sh** Script to run all metric calculations.
- **execute-perf.sh** Script to run all perfromance measurements. You may run as root to change the real-time scheduling.
- **execute-valid.sh** Script to run the perfromance measurements of the matrix multiplication. You may run as root to change the real-time scheduling.