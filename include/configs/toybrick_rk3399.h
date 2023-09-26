/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * (C) Copyright 2021 Capgemini Engineering
 */

#ifndef __TOYBRICK_RK3399_H
#define __TOYBRICK_RK3399_H

#define ROCKCHIP_DEVICE_SETTINGS \
		"stdin=serial,usbkbd\0" \
		"stdout=serial,vidconsole\0" \
		"stderr=serial,vidconsole\0"

#include <configs/rk3399_common.h>

#define SDRAM_BANK_SIZE			(2UL << 30)

#endif
