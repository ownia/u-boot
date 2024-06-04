/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (c) 2023 Rockchip Electronics Co., Ltd.
 */

#ifndef __EVB_RK3588_H
#define __EVB_RK3588_H

#include <configs/rk3588_common.h>

#define ARMSOM_SIGE7__UBOOT_IMAGE_GUID \
	EFI_GUID(0xb62dbe3f, 0x385d, 0x4bcf, 0x8c, 0x0f, \
		 0x5c, 0xd7, 0x5c, 0x98, 0x3b, 0x08)

#define ROCKCHIP_DEVICE_SETTINGS \
		"stdout=serial,vidconsole\0" \
		"stderr=serial,vidconsole\0"

#endif
