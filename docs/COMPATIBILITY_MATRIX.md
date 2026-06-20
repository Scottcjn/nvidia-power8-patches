# POWER8 NVIDIA Compatibility Matrix

This matrix summarizes the combinations currently documented in this repository. It is intentionally conservative: rows marked `not yet verified` or `not documented` should be treated as open validation work, not as hardware support claims.

## Known Configurations

| POWER8 system model | Distro / kernel | GPU model | Driver branch | CUDA / userspace | Connection method | Boot / build flags | Status | Caveats | Source |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| IBM Power System S824 (8286-42A), dual 8-core POWER8, 576 GB RAM | Ubuntu 20.04 LTS, kernel 5.4.0-216-generic | Tesla V100 32GB | NVIDIA open GPU kernel modules 550.54.14 | ppc64le CUDA userspace not pinned; README points to IBM Advance Toolchain, NVIDIA HPC SDK for Power9, and legacy CUDA 10.x/11.x ppc64le packages | OCuLink via Supermicro AOC-SLG3-2E4T host card, SFF-8611 cable, Minisforum DEG1 GPU dock, external ATX PSU | `CC=gcc-10`, `CXX=g++-10`, copy `nv-ibmnpu.h`, `nv-ibmnpu.c`, and `ibmnpu_linux.h` into `kernel-open/nvidia/`, then `make -j$(nproc) modules` | Driver compiles; testing in progress | Runtime CUDA workload and long-running stability are not yet documented for this POWER8/V100 row | README `Test System`, `OCuLink Connection Method`, `Installation Instructions`, and `Confirmed Working Configurations` |
| IBM POWER8 class system | Not documented | Ampere RTX 30-series | Not documented | Not documented | Standard PCIe or OCuLink expected, but exact wiring not documented | Not documented | Architecture listed as tested | No specific POWER8 host, driver branch, CUDA version, or card SKU is tied to the tested status in the README | README `Supported GPU Architectures` |
| IBM POWER8 class system | Not documented | Turing RTX 20-series | Not documented | Not documented | Standard PCIe or OCuLink expected, but exact wiring not documented | Not documented | Architecture listed as tested | No specific POWER8 host, driver branch, CUDA version, or card SKU is tied to the tested status in the README | README `Supported GPU Architectures` |
| IBM POWER8 class system | Not documented | Volta Tesla V100 / Titan V | 550.54.14 documented for the S824 test system | ppc64le CUDA userspace options documented, but exact installed version not documented | OCuLink documented for the Tesla V100 32GB row | GCC 10 documented for building nvidia-open | V100 32GB compile path documented; testing in progress | Treat V100 runtime support as unverified until `nvidia-smi`, CUDA sample output, or workload logs are added | README `Supported GPU Architectures`, `Test System`, and `Confirmed Working Configurations` |
| IBM POWER8 class system | Not documented | Ada Lovelace RTX 40-series | Not documented | Not documented | Not documented | Not documented | Supported | Architecture support is listed, but there is no known-good POWER8 host row yet | README `Supported GPU Architectures` |
| IBM POWER8 class system | Not documented | Blackwell RTX 5070 / 5080 / 5090 | Not documented for POWER8 | Not documented for POWER8 | Not documented for POWER8 | Not documented for POWER8 | Inference confirmed on x86_64 Linux only | Do not treat the RTX 5070 inference row as POWER8 validation; the README explicitly lists the host as x86_64 Linux | README `Supported GPU Architectures` and `Confirmed Working Configurations` |
| IBM POWER8 class system | Not documented | Pascal Tesla P100 / P40 / P4 / GTX 1080 Ti | Not documented | Not documented | Not documented | Not documented | Supported | No known-good POWER8 validation row is documented yet | README `Supported GPU Architectures` |
| IBM POWER8 class system | Not documented | Maxwell Tesla M40 / M60 / GTX Titan X | Not documented | Not documented | Not documented | Not documented | Supported | No known-good POWER8 validation row is documented yet | README `Supported GPU Architectures` |
| IBM POWER8 class system | Not documented | Kepler Tesla K80 / K40 / K20 | Not documented | Not documented | Not documented | Not documented | Supported | Tesla K80-class cards may need special auxiliary power; no known-good POWER8 validation row is documented yet | README `Supported GPU Architectures` and `Troubleshooting` |

## Evidence Gaps To Fill

- POWER8 runtime proof for each GPU row: `lspci`, `nvidia-smi`, `lsmod | grep nvidia`, and `dmesg | grep -i nvidia` output.
- Exact CUDA package version used on ppc64le, plus one CUDA sample or inference workload result.
- Exact PCIe or OCuLink topology for non-V100 GPUs, including cable, dock, power supply, and slot information.
- Any required Petitboot, kernel command line, IOMMU, or module-loading flags beyond the documented GCC 10 build environment.
- Known-bad combinations, especially cards that enumerate on PCIe but fail module load or CUDA initialization.

## How To Report A New Row

Open an issue or pull request with the matrix columns above and include command output or build logs where possible. Mark uncertain fields as `not documented` rather than guessing.
