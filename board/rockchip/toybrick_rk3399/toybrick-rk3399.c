// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2021 Capgemini Engineering
 */

#include <common.h>
#include <dm.h>
#include <init.h>
#include <log.h>
#include <syscon.h>
#include <asm/io.h>
#include <asm/arch-rockchip/clock.h>
#include <asm/arch-rockchip/periph.h>
#include <asm/arch-rockchip/grf_rk3399.h>
#include <asm/arch-rockchip/hardware.h>
#include <asm/arch-rockchip/misc.h>

#include <dfu.h>
#include <env.h>

#define GRF_IO_VSEL_BT565_SHIFT 0
#define GRF_IO_VSEL_ADDR  0xff77e640

int board_early_init_f(void)
{
	/* BT565 is in 1.8v domain */
	rk_setreg(GRF_IO_VSEL_ADDR, 1 << GRF_IO_VSEL_BT565_SHIFT);

	return 0;
}

/* ALT_INFO Macro Function below added for DFU_ALT_INFO */
#ifdef CONFIG_SET_DFU_ALT_INFO
#define CONFIG_DFU_ALT_BOOT_SD \
	"mmc 1=idbloader-img raw 0x40 0x2000;u-boot-itb raw 0x4000 0x2000\0"
#define CONFIG_DFU_ALT_BOOT_EMMC \
	"mmc 0=idbloader-img raw 0x40 0x2000;u-boot-itb raw 0x4000 0x2000\0"

void set_dfu_alt_info(char *interface, char *devstr)
{
	char *alt_info;
	struct mmc *mmc;
	int dev_num = 0;
	alt_info = env_get("dfu_alt_info");
	if (alt_info)
		return;
	dev_num = simple_strtoul(devstr ? devstr:"0", NULL, 10);
	mmc = find_mmc_device(dev_num);
	if (!mmc || mmc_init(mmc))
		return;
	alt_info = IS_SD(mmc) ? CONFIG_DFU_ALT_BOOT_SD : CONFIG_DFU_ALT_BOOT_EMMC;
	env_set("dfu_alt_info", alt_info);
}
#endif
