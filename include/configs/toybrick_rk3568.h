/* SPDX-License-Identifier: GPL-2.0+ */

#ifndef __TOYBRICK_RK3568_H
#define __TOYRBICK_RK3568_H

#include <configs/rk3568_common.h>

#define ROCKCHIP_DEVICE_SETTINGS \
			"stdin=serial,usbkbd\0" \
			"stdout=serial,vidconsole\0" \
			"stderr=serial,vidconsole\0"

#endif
