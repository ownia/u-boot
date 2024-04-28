// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2023 Rockchip Electronics Co,. Ltd.
 */

#include <efi_loader.h>
#include <fdtdec.h>
#include <fdt_support.h>

#define TOYBRICK_RK3588_UPDATABLE_IMAGES	1
#define ROCKCHIP_UBOOT_IMAGE_GUID \
	EFI_GUID(0x5452a04a, 0x462d, 0x4433, 0x97, 0x78, \
		 0x2b, 0x52, 0x59, 0x27, 0x7b, 0xb3)

#if IS_ENABLED(CONFIG_EFI_HAVE_CAPSULE_SUPPORT)
struct efi_fw_image fw_images[TOYBRICK_RK3588_UPDATABLE_IMAGES] = {0};

struct efi_capsule_update_info update_info = {
	.dfu_string = "mmc 0=u-boot.itb raw 0x4000 0x2000",
	.num_images = TOYBRICK_RK3588_UPDATABLE_IMAGES,
	.images = fw_images,
};
#endif /* EFI_HAVE_CAPSULE_SUPPORT */

#ifndef CONFIG_SPL_BUILD
#if IS_ENABLED(CONFIG_EFI_HAVE_CAPSULE_SUPPORT) && IS_ENABLED(CONFIG_EFI_PARTITION)
void rockchip_capsule_update_board_setup(void)
{
	efi_guid_t uboot_image_type_guid = ROCKCHIP_UBOOT_IMAGE_GUID;

	guidcpy(&fw_images[0].image_type_id, &uboot_image_type_guid);
	fw_images[0].fw_name = u"ROCKCHIP_UBOOT";
	fw_images[0].image_index = 1;
}
#endif /* CONFIG_EFI_HAVE_CAPSULE_SUPPORT && CONFIG_EFI_PARTITION */
#endif /* !CONFIG_SPL_BUILD */

#ifdef CONFIG_OF_BOARD_SETUP
static int configure_systemready_fdt_nodes(void *blob)
{
	const char *dmc_compatible = "rockchip,rk3588-dmc";
	int off = fdt_node_offset_by_compatible(blob, -1, dmc_compatible);
	int err = 0;

	if (off < 0) {
		printf("not find dmc node\n");
		return off;
	}

	err = fdt_del_node(blob, off);
	if (err < 0) {
		printf("could not remove dmc\n");
		return err;
	}

	return 0;
}

int ft_board_setup(void *blob, struct bd_info *bd)
{
	int ret = 0;

	ret = configure_systemready_fdt_nodes(blob);

	return ret;
}
#endif
