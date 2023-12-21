/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (c) 2023 Rockchip Electronics Co., Ltd.
 */

#ifndef __EVB_RK3588_H
#define __EVB_RK3588_H

#include <configs/rk3588_common.h>

#define ROCKCHIP_UBOOT_IMAGE_GUID \
	EFI_GUID(0x5452a04a, 0x462d, 0x4433, 0x97, 0x78, \
		 0x2b, 0x52, 0x59, 0x27, 0x7b, 0xb3)

#define ROCKCHIP_DEVICE_SETTINGS \
		"stdout=serial,vidconsole\0" \
		"stderr=serial,vidconsole\0"

#endif
