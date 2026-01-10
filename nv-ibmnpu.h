/*
 * NVIDIA Open-Source Driver - IBM POWER8 NPU Stubs
 *
 * POWER8 does not have IBM NPU/NVLink hardware (that's POWER9+).
 * This file provides stub implementations so the driver compiles on POWER8.
 *
 * Copyright (c) 2025 Elyan Labs
 * License: MIT/Apache 2.0 (same as nvidia-open)
 */

#ifndef _NV_IBMNPU_H_
#define _NV_IBMNPU_H_

#include "nvtypes.h"

/* Constants that would be defined for real NPU */
#define NV_MAX_ATTACHED_IBMNPUS 6
#define nv_volta_dma_addr_size 47
#define nv_volta_addr_space_width 0

/* NUMA info structure stub */
typedef struct nv_npu_numa_info {
    NvU64 compr_sys_phys_addr;
    NvU64 guest_phys_addr;
} nv_npu_numa_info_t;

/* NPU info structure stub - matches what nv.c expects */
struct nv_ibmnpu_info {
    int dummy;
    nv_npu_numa_info_t numa_info;
    void *devs[NV_MAX_ATTACHED_IBMNPUS];
    int num_devs;
};

/* Forward declare nv_state_t */
struct nv_state_t;
typedef struct nv_state_t nv_state_t;

/* IBM NPU global init/exit - no-ops on POWER8 */
static inline int ibmnpu_init(void) { return 0; }
static inline void ibmnpu_exit(void) { }

/* Per-device NPU functions - all no-ops */
static inline void nv_init_ibmnpu_info(nv_state_t *nv) { }
static inline void nv_destroy_ibmnpu_info(nv_state_t *nv) { }
static inline int nv_init_ibmnpu_devices(nv_state_t *nv) { return 0; }
static inline void nv_unregister_ibmnpu_devices(nv_state_t *nv) { }
static inline int nv_get_ibmnpu_chip_id(nv_state_t *nv) { return -1; }
static inline void nv_ibmnpu_cache_flush_numa_region(nv_state_t *nv) { }

#endif /* _NV_IBMNPU_H_ */
