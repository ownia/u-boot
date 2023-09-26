// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2021 Capgemini Engineering
 */

#include <common.h>
#include <dm.h>
#include <efi_loader.h>
#include <init.h>
#include <log.h>
#include <syscon.h>
#include <asm/io.h>
#include <asm/arch-rockchip/clock.h>
#include <asm/arch-rockchip/periph.h>
#include <asm/arch-rockchip/grf_rk3399.h>
#include <asm/arch-rockchip/hardware.h>
#include <asm/arch-rockchip/misc.h>

#define GRF_IO_VSEL_BT565_SHIFT 0
#define GRF_IO_VSEL_ADDR  0xff77e640

#define TOYBRICK_UPDATABLE_IMAGES	2

#if IS_ENABLED(CONFIG_EFI_HAVE_CAPSULE_SUPPORT)
static struct efi_fw_image fw_images[TOYBRICK_UPDATABLE_IMAGES] = {0};

struct efi_capsule_update_info update_info = {
	.images = fw_images,
};

u8 num_image_type_guids = TOYBRICK_UPDATABLE_IMAGES;
#endif

int board_early_init_f(void)
{
	/* BT565 is in 1.8v domain */
	rk_setreg(GRF_IO_VSEL_ADDR, 1 << GRF_IO_VSEL_BT565_SHIFT);

	return 0;
}

#ifndef CONFIG_SPL_BUILD
#if defined(CONFIG_EFI_HAVE_CAPSULE_SUPPORT) && defined(CONFIG_EFI_PARTITION)
void rockchip_capsule_update_board_setup(void)
{
	efi_guid_t idbldr_image_type_guid =
		ROCKPI_4B_IDBLOADER_IMAGE_GUID;
	efi_guid_t uboot_image_type_guid = ROCKPI_4B_UBOOT_IMAGE_GUID;

	guidcpy(&fw_images[0].image_type_id, &idbldr_image_type_guid);
	guidcpy(&fw_images[1].image_type_id, &uboot_image_type_guid);

	fw_images[0].fw_name = u"TOYBRICK-IDBLOADER";
	fw_images[1].fw_name = u"TOYBRICK-UBOOT";
}
#endif /* CONFIG_EFI_HAVE_CAPSULE_SUPPORT && CONFIG_EFI_PARTITION */
#endif /* !CONFIG_SPL_BUILD */
