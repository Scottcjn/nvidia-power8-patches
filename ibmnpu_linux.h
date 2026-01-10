/*
 * NVIDIA Open-Source Driver - IBM NPU Linux Kernel Interface Stubs
 *
 * This header provides stub definitions for the IBM NPU Linux kernel
 * interface functions that don't exist on POWER8.
 *
 * Copyright (c) 2025 Elyan Labs
 * License: MIT/Apache 2.0 (same as nvidia-open)
 */

#ifndef _IBMNPU_LINUX_H_
#define _IBMNPU_LINUX_H_

#include <linux/types.h>

/* Stub structure for genregs info */
typedef struct {
    u64 addr;
    u64 size;
} ibmnpu_genregs_info_t;

/* Stub functions - POWER8 has no NPU */
static inline int ibmnpu_init(void) { return 0; }
static inline void ibmnpu_exit(void) { }
static inline int ibmnpu_get_genreg_info(struct pci_dev *dev, ibmnpu_genregs_info_t *info) { return -ENODEV; }
static inline int ibmnpu_get_relaxed_ordering_mode(struct pci_dev *dev, bool *mode) { return -ENODEV; }
static inline void ibmnpu_wait_for_rsync(struct pci_dev *dev) { }
static inline void ibmnpu_cache_flush_range(struct pci_dev *dev, u64 start, u64 end) { }

#endif /* _IBMNPU_LINUX_H_ */
