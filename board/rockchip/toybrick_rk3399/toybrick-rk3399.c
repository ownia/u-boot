// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2021 Capgemini Engineering
 */

#include <common.h>
#include <dm.h>
#include <init.h>
#include <log.h>
#include <syscon.h>
#include <dfu.h>
#include <env.h>
#include <asm/io.h>
#include <asm/arch-rockchip/clock.h>
#include <asm/arch-rockchip/periph.h>
#include <asm/arch-rockchip/grf_rk3399.h>
#include <asm/arch-rockchip/hardware.h>
#include <asm/arch-rockchip/misc.h>

#define GRF_BASE        0xff770000
int board_early_init_f(void)
{
	struct rk3399_grf_regs *grf = (void *)GRF_BASE;

	rk_setreg(&grf->io_vsel, BIT(0));
	return 0;
}

/* ALT_INFO Macro Function below added for DFU_ALT_INFO */
#ifdef CONFIG_SET_DFU_ALT_INFO
#define CONFIG_DFU_ALT_BOOT_SD \
	"mmc 1=idbloader-img raw 0x40 0x2000;u-boot-itb raw 0x4000 0x2000\0"
#define CONFIG_DFU_ALT_BOOT_EMMC \
	"mmc 0=idbloader-img raw 0x40 0x2000 mmcpart 1;u-boot-itb raw 0x4000 0x2000 mmcpart 1\0"

void set_dfu_alt_info(char *interface, char *devstr)
{
	char *alt_info;
	struct mmc *mmc;
	int dev_num = 0;
	alt_info = env_get("dfu_alt_info");
	if (alt_info)
		return;

	/* Default to eMMC */
	alt_info = CONFIG_DFU_ALT_BOOT_EMMC;

	dev_num = simple_strtoul(devstr ? devstr : "0", NULL, 10);
	mmc = find_mmc_device(dev_num);
	if (mmc && !mmc_init(mmc) && IS_SD(mmc))
		alt_info = CONFIG_DFU_ALT_BOOT_SD;

	env_set("dfu_alt_info", alt_info);
}
#endif
