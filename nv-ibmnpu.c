/*
 * NVIDIA Open-Source Driver - IBM POWER8 NPU Stub Implementations
 *
 * These functions are exported symbols required by the driver but
 * have no implementation on POWER8 (NVLink only exists on POWER9+).
 *
 * Copyright (c) 2025 Elyan Labs
 * License: MIT/Apache 2.0 (same as nvidia-open)
 */

#include "nvtypes.h"
#include "nv-linux.h"

/*
 * nv_get_ibmnpu_genreg_info - Get NPU general register info
 *
 * On POWER8, there is no NPU, so return not supported.
 */
NV_STATUS NV_API_CALL nv_get_ibmnpu_genreg_info(nv_state_t *nv, NvU64 *addr, NvU64 *size, void **map)
{
    if (addr) *addr = 0;
    if (size) *size = 0;
    if (map) *map = NULL;
    return NV_ERR_NOT_SUPPORTED;
}

/*
 * nv_get_ibmnpu_relaxed_ordering_mode - Check NPU relaxed ordering
 *
 * On POWER8, there is no NPU, so always return false.
 */
NV_STATUS NV_API_CALL nv_get_ibmnpu_relaxed_ordering_mode(nv_state_t *nv, NvBool *mode)
{
    if (mode) *mode = NV_FALSE;
    return NV_ERR_NOT_SUPPORTED;
}

/*
 * nv_wait_for_ibmnpu_rsync - Wait for NPU rsync
 *
 * On POWER8, there is no NPU rsync to wait for.
 */
void NV_API_CALL nv_wait_for_ibmnpu_rsync(nv_state_t *nv)
{
    /* No NPU rsync needed on POWER8 */
}

/*
 * nv_ibmnpu_cache_flush_range - Flush NPU cache range
 *
 * On POWER8, there is no NPU cache to flush.
 */
void NV_API_CALL nv_ibmnpu_cache_flush_range(nv_state_t *nv, NvU64 start, NvU64 end)
{
    /* No NPU cache to flush on POWER8 */
}
