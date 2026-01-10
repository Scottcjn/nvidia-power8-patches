# NVIDIA Open-Source Driver Patches for IBM POWER8

**World's First NVIDIA Open-Source Kernel Driver for POWER8/PPC64LE!**

These patches enable compilation of the NVIDIA open-source GPU kernel modules on IBM POWER8 systems (PPC64LE architecture). Successfully compiled on January 10, 2025.

## Background

The NVIDIA open-source kernel driver (`nvidia-open`) has PowerPC support, but targets POWER9+ systems with NVLink (IBM NPU). POWER8 systems like the IBM S824 do not have NVLink/NPU hardware, but can still use NVIDIA GPUs via standard PCIe.

These patches stub out the IBM NPU functions that are not available on POWER8, allowing the driver to compile and potentially work with PCIe-connected GPUs (GeForce, Tesla, etc.) via OCuLink or standard PCIe slots.

## Test System

- **Hardware**: IBM Power System S824 (8286-42A)
- **CPU**: Dual 8-core POWER8 (16 cores, 128 threads with SMT8)
- **RAM**: 576 GB DDR3
- **OS**: Ubuntu 20.04 LTS (Focal Fossa)
- **Kernel**: 5.4.0-216-generic
- **GCC**: 10.2.0
- **NVIDIA Driver Version**: 550.54.14 (nvidia-open)

## GPU Connectivity Tested

- **OCuLink**: Supermicro AOC-SLG3-2E4T NVMe switch repurposed for GPU passthrough
- **Tested GPUs**: RX 580 via OCuLink confirmed working with amdgpu
- **Target GPUs**: RTX 2060, RTX 3060, Tesla K80, M40, V100

## Patches Included

### 1. `nv-ibmnpu.h` (New File)
POWER8 stub header providing:
- `nv_npu_numa_info_t` structure definition
- `nv_ibmnpu_info` structure definition
- Inline stub functions for NPU init/exit
- Constants (`NV_MAX_ATTACHED_IBMNPUS`, etc.)

### 2. `nv-ibmnpu.c` (New File)
Stub implementations for exported NPU functions:
- `nv_get_ibmnpu_genreg_info()`
- `nv_get_ibmnpu_relaxed_ordering_mode()`
- `nv_wait_for_ibmnpu_rsync()`
- `nv_ibmnpu_cache_flush_range()`

### 3. `ibmnpu_linux.h` (Stub Header)
Fallback header for IBM NPU Linux kernel interface.

## Installation

```bash
# Download nvidia-open source
wget https://github.com/NVIDIA/open-gpu-kernel-modules/archive/refs/tags/550.54.14.tar.gz
tar xzf 550.54.14.tar.gz
cd open-gpu-kernel-modules-550.54.14

# Apply patches
cp /path/to/patches/nv-ibmnpu.h kernel-open/nvidia/
cp /path/to/patches/nv-ibmnpu.c kernel-open/nvidia/
cp /path/to/patches/ibmnpu_linux.h kernel-open/nvidia/

# Build
make -j$(nproc) modules
```

## Build Output

All 5 kernel modules compile successfully:
- `nvidia.ko` (14.9 MB)
- `nvidia-modeset.ko` (3.0 MB)
- `nvidia-uvm.ko` (2.9 MB)
- `nvidia-drm.ko` (198 KB)
- `nvidia-peermem.ko` (24 KB)

## Status

- [x] Kernel modules compile
- [ ] Modules load without GPU (testing)
- [ ] RTX 2060 via OCuLink detection
- [ ] CUDA userspace (need ppc64le libraries)
- [ ] Basic CUDA compute test

## Why This Matters

1. **First POWER8 NVIDIA Driver**: Opens possibility of using modern NVIDIA GPUs on POWER8 servers
2. **OCuLink GPU Expansion**: External GPU connectivity proven working on POWER8
3. **Legacy Server Revival**: 576GB RAM + modern GPU = interesting AI/ML platform
4. **Community Contribution**: Patches available for others with POWER8 systems

## Credits

- **Development**: Elyan Labs (Scott Boudreaux)
- **Testing Platform**: IBM POWER8 S824 with 576GB RAM
- **Assistance**: Claude AI (Anthropic)

## License

Patches are provided under the same license as the NVIDIA open-source driver (MIT/Apache 2.0 dual license).

## Contact

For questions or contributions, open an issue on this repository.
