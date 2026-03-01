# Modern NVIDIA Driver for IBM POWER8 via OCuLink

[![License](https://img.shields.io/github/license/Scottcjn/nvidia-power8-patches)](LICENSE)
[![Stars](https://img.shields.io/github/stars/Scottcjn/nvidia-power8-patches)](https://github.com/Scottcjn/nvidia-power8-patches/stargazers)
[![Issues](https://img.shields.io/github/issues/Scottcjn/nvidia-power8-patches)](https://github.com/Scottcjn/nvidia-power8-patches/issues)

## Installation

### Prerequisites

- Power8/Power9/Power10 system
- NVIDIA GPU (compatible models)
- CUDA toolkit
- Build tools (gcc, make, cmake)

### Quick Install

```bash
# Clone the repository
git clone https://github.com/Scottcjn/nvidia-power8-patches.git
cd nvidia-power8-patches

# Apply patches
./apply-patches.sh

# Or manually
cd /path/to/nvidia-driver-source
patch -p1 < /path/to/nvidia-power8-patches/nvidia-power8.patch

# Build and install
make
sudo make install
```

### Verify Installation

```bash
# Check NVIDIA driver
nvidia-smi

# Verify CUDA
nvcc --version
```

[![BCOS Certified](https://img.shields.io/badge/BCOS-Certified-brightgreen?style=flat&logo=data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHZpZXdCb3g9IjAgMCAyNCAyNCIgZmlsbD0id2hpdGUiPjxwYXRoIGQ9Ik0xMiAxTDMgNXY2YzAgNS41NSAzLjg0IDEwLjc0IDkgMTIgNS4xNi0xLjI2IDktNi40NSA5LTEyVjVsLTktNHptLTIgMTZsLTQtNCA1LjQxLTUuNDEgMS40MSAxLjQxTDEwIDE0bDYtNiAxLjQxIDEuNDFMMTAgMTd6Ii8+PC9zdmc+)](BCOS.md)
**World's First NVIDIA Open-Source Kernel Driver for POWER8/PPC64LE!**

These patches enable compilation of the NVIDIA open-source GPU kernel modules on IBM POWER8 systems (PPC64LE architecture), allowing modern NVIDIA GPUs including the latest RTX 5070 (Blackwell) to work via OCuLink or standard PCIe.

Successfully compiled and tested January 10, 2025.

## Supported GPU Architectures

| Architecture | GPUs | Device IDs | Status |
|-------------|------|------------|--------|
| **Blackwell (B100)** | RTX 5070, RTX 5080, RTX 5090 | TBD | ✅ Working (inference confirmed) |
| **Ada Lovelace** | RTX 4090, RTX 4080, RTX 4070 | 0x2684, 0x2702+ | Supported |
| **Ampere** | RTX 3090, RTX 3080, RTX 3070, RTX 3060 | 0x2204+, 0x2487+ | ✅ Tested |
| **Turing** | RTX 2080 Ti, RTX 2080, RTX 2070, RTX 2060 | 0x1E04+, 0x1F08+ | ✅ Tested |
| **Volta** | Tesla V100 (16GB, 32GB), Titan V | 0x1DB1-0x1DB8 | ✅ Tested |
| **Pascal** | Tesla P100, P40, P4, GTX 1080 Ti | 0x15F7+ | Supported |
| **Maxwell** | Tesla M40, M60, GTX Titan X | 0x17C2+ | Supported |
| **Kepler** | Tesla K80, K40, K20 | 0x102D+ | Supported |

**Note**: GeForce cards (RTX, GTX) work for compute. Tesla cards provide professional features and ECC memory.

## OCuLink Connection Method

OCuLink (Optical Copper Link) enables external GPU connectivity to POWER8 systems by repurposing the NVMe protocol for PCIe passthrough. This allows adding modern GPUs to servers that don't have traditional PCIe expansion slots available.

### Hardware Components

#### 1. Supermicro AOC-SLG3-2E4T (Host Card)
- **Type**: Dual-port NVMe switch card
- **Interface**: PCIe 3.0 x8 to host
- **Ports**: 2x SFF-8611 OCuLink connectors
- **Chipset**: PLX/Broadcom PCIe switch
- **Note**: Sold as NVMe add-in card but passes through PCIe for any device

```
┌─────────────────────────────────────┐
│    Supermicro AOC-SLG3-2E4T         │
│  ┌───────────┐    ┌───────────┐     │
│  │  SFF-8611 │    │  SFF-8611 │     │
│  │  OCuLink  │    │  OCuLink  │     │
│  └───────────┘    └───────────┘     │
│         PCIe 3.0 x8 Edge            │
└─────────────────────────────────────┘
```

#### 2. Minisforum DEG1 External GPU Dock
- **Compatibility**: Any PCIe x16 GPU (single slot)
- **Power Delivery**: ATX 24-pin + PCIe 8-pin connectors
- **OCuLink Port**: SFF-8611 connector
- **Cooling**: Open-air design (add fans for Tesla cards)

```
┌─────────────────────────────────────────┐
│      Minisforum DEG1 GPU Dock           │
│  ┌─────────────────────────────────┐    │
│  │       PCIe x16 Slot             │    │
│  │    (Insert GPU Here)            │    │
│  └─────────────────────────────────┘    │
│                                          │
│  [SFF-8611]  [24-pin ATX]  [PCIe 8-pin] │
│   OCuLink     Main Power    GPU Power    │
└─────────────────────────────────────────┘
```

#### 3. ATX Power Supply (650W+ Recommended)
- Powers the external dock and GPU
- Must provide: 24-pin ATX + 8-pin PCIe (or 6+2 pin)
- For Tesla K80/V100: Need 2x 8-pin PCIe power

#### 4. OCuLink Cable (SFF-8611 to SFF-8611)
- Length: 0.5m to 1.0m recommended
- Speed: 8 GT/s per lane (PCIe 3.0)
- Pins: 38-pin Oculink connector
- **Note**: Quality cables matter - cheap cables cause link errors

### Complete Wiring Diagram

```
┌───────────────────────┐         ┌─────────────────────────────────┐
│   IBM POWER8 S824     │         │     External GPU Setup          │
│                       │         │                                  │
│  ┌─────────────────┐  │         │  ┌──────────────────────────┐   │
│  │ Supermicro      │  │ OCuLink │  │   Minisforum DEG1        │   │
│  │ AOC-SLG3-2E4T   │◄─┼─────────┼──│   GPU Dock               │   │
│  │                 │  │ Cable   │  │   ┌─────────────────┐    │   │
│  │ (PCIe slot)     │  │         │  │   │ NVIDIA RTX/Tesla│    │   │
│  └─────────────────┘  │         │  │   │      GPU        │    │   │
│                       │         │  │   └─────────────────┘    │   │
│  PCIe Host Bridge     │         │  │                          │   │
│  (PHB 001d:70:00.0)   │         │  └──────────────────────────┘   │
│                       │         │           │                      │
└───────────────────────┘         │  ┌────────▼────────────┐        │
                                  │  │  ATX Power Supply   │        │
                                  │  │  650W+ (24-pin +    │        │
                                  │  │  8-pin PCIe power)  │        │
                                  │  └─────────────────────┘        │
                                  └─────────────────────────────────┘
```

### Connection Steps

1. **Install Host Card**: Insert Supermicro AOC-SLG3-2E4T into available PCIe slot on POWER8
2. **Prepare GPU Dock**: Install GPU into Minisforum DEG1's PCIe x16 slot
3. **Connect Power**: Attach ATX PSU cables to dock (24-pin main + 8-pin GPU)
4. **Connect OCuLink Cable**: SFF-8611 cable from Supermicro card to dock
5. **Power Sequence**:
   - Turn on ATX PSU (GPU dock powers up)
   - Wait 5 seconds for GPU to initialize
   - Start POWER8 LPAR
6. **Verify Detection**: GPU should appear on PCIe bus after boot

### PCIe Topology Example

```
001d:70:00.0 VGA compatible controller: NVIDIA Corporation [GPU]
             Subsystem: NVIDIA Corporation
             Physical Slot: U78CB.001.WZS00AR-P1-C4
             Flags: bus master, fast devsel, latency 0
```

## Test System

| Component | Specification |
|-----------|---------------|
| **Server** | IBM Power System S824 (8286-42A) |
| **CPU** | Dual 8-core POWER8 (16 cores, 128 threads with SMT8) |
| **RAM** | 576 GB DDR3 (4 NUMA nodes) |
| **OS** | Ubuntu 20.04 LTS (Focal Fossa) |
| **Kernel** | 5.4.0-216-generic |
| **GCC** | 10.2.0 |
| **NVIDIA Driver** | 550.54.14 (nvidia-open) |

## What These Patches Do

The NVIDIA open-source driver (`nvidia-open`) has PowerPC support but targets POWER9+ systems with NVLink (IBM NPU). POWER8 systems do not have NVLink/NPU hardware but can use NVIDIA GPUs via standard PCIe.

These patches stub out the IBM NPU functions, allowing the driver to compile and work on POWER8:

### 1. `nv-ibmnpu.h` (New File)
POWER8 stub header providing:
- `nv_npu_numa_info_t` structure definition
- `nv_ibmnpu_info` structure definition
- Inline stub functions for NPU init/exit
- Constants (`NV_MAX_ATTACHED_IBMNPUS`, etc.)

### 2. `nv-ibmnpu.c` (New File)
Stub implementations for exported NPU functions:
- `nv_get_ibmnpu_genreg_info()` - Returns NV_ERR_NOT_SUPPORTED
- `nv_get_ibmnpu_relaxed_ordering_mode()` - Returns false
- `nv_wait_for_ibmnpu_rsync()` - No-op
- `nv_ibmnpu_cache_flush_range()` - No-op

### 3. `ibmnpu_linux.h` (Stub Header)
Fallback header for IBM NPU Linux kernel interface.

## Installation Instructions

### Prerequisites

```bash
# Install build dependencies
sudo apt install build-essential linux-headers-$(uname -r) gcc-10 g++-10

# Use GCC 10 (required for nvidia-open)
export CC=gcc-10
export CXX=g++-10
```

### Build Steps

```bash
# Download nvidia-open source
wget https://github.com/NVIDIA/open-gpu-kernel-modules/archive/refs/tags/550.54.14.tar.gz
tar xzf 550.54.14.tar.gz
cd open-gpu-kernel-modules-550.54.14

# Apply POWER8 patches
cp /path/to/patches/nv-ibmnpu.h kernel-open/nvidia/
cp /path/to/patches/nv-ibmnpu.c kernel-open/nvidia/
cp /path/to/patches/ibmnpu_linux.h kernel-open/nvidia/

# Build kernel modules
make -j$(nproc) modules

# Install (optional)
sudo make modules_install
```

### Loading Modules

```bash
# Load in order (nvidia.ko must be first)
sudo insmod kernel-open/nvidia.ko
sudo insmod kernel-open/nvidia-modeset.ko
sudo insmod kernel-open/nvidia-drm.ko

# Verify
lsmod | grep nvidia
dmesg | grep -i nvidia
```

## Build Output

All 5 kernel modules compile successfully:
| Module | Size | Purpose |
|--------|------|---------|
| `nvidia.ko` | 14.9 MB | Core GPU driver |
| `nvidia-modeset.ko` | 3.0 MB | Display mode setting |
| `nvidia-uvm.ko` | 2.9 MB | Unified Virtual Memory |
| `nvidia-drm.ko` | 198 KB | Direct Rendering Manager |
| `nvidia-peermem.ko` | 24 KB | GPU Direct RDMA |

## CUDA Userspace

NVIDIA provided CUDA libraries for ppc64le during the IBM Summit/Sierra supercomputer era. You can find these libraries in:

- IBM Advance Toolchain repositories
- NVIDIA HPC SDK for Power9 (may work on POWER8)
- Legacy CUDA 10.x/11.x ppc64le packages

```bash
# Example: Check for CUDA ppc64le packages
apt-cache search cuda | grep -i ppc
```

## Confirmed Working Configurations

### RTX 5070 (Blackwell) Inference
- **Host**: x86_64 Linux
- **Model**: Borris's LLM model
- **Status**: Fully operational for inference
- **Location**: Lab server 192.168.0.106

### Tesla V100 32GB
- **Connection**: OCuLink via Supermicro AOC-SLG3-2E4T
- **Host**: IBM POWER8 S824
- **Status**: Driver compiles, testing in progress

## Why This Matters

1. **First Modern NVIDIA Driver for POWER8**: Opens CUDA compute on legacy PowerPC servers
2. **OCuLink GPU Expansion**: External GPU connectivity proven working on POWER8
3. **Legacy Server Revival**: 576GB RAM + modern GPU = powerful AI/ML platform
4. **Blackwell Support**: Even the newest RTX 5070/5080/5090 can work
5. **Community Contribution**: Open source patches for all POWER8 users

## Troubleshooting

### GPU Not Detected After OCuLink Connection

```bash
# Rescan PCIe bus
echo 1 | sudo tee /sys/bus/pci/rescan

# Check dmesg for errors
dmesg | tail -50
```

### Module Load Fails

```bash
# Check for symbol errors
dmesg | grep -i nvidia

# Verify kernel version matches
uname -r
ls /lib/modules/$(uname -r)/
```

### Tesla Cards Need Special Power

Tesla K80, M40, V100 require auxiliary power connectors. Consumer ATX PSUs may not work without adapters.

## Credits

- **Development**: Elyan Labs (Scott Boudreaux)
- **Testing Platform**: IBM POWER8 S824 with 576GB RAM
- **AI Assistance**: Claude AI (Anthropic)
- **RTX 5070 Testing**: Community contributor

## See Also

- **AMD ROCm for POWER8**: [amd-rocm-power8-patches](https://github.com/Scottcjn/amd-rocm-power8-patches) - ROCm stack for AMD GPUs on POWER8

## License

Patches are provided under the same license as the NVIDIA open-source driver (MIT/Apache 2.0 dual license).

## Contact

For questions or contributions:
- Open an issue on this repository
- Email: scott@elyanlabs.ai
