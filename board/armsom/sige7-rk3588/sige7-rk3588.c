// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2023 Rockchip Electronics Co,. Ltd.
 */

#include <dm.h>
#include <efi_loader.h>
#include <fdtdec.h>
#include <fdt_support.h>

#if IS_ENABLED(CONFIG_EFI_HAVE_CAPSULE_SUPPORT)
struct efi_fw_image fw_images[] = {
	{
		.image_type_id = ARMSOM_SIGE7_UBOOT_IMAGE_GUID,
		.fw_name = u"ROCKCHIP_UBOOT",
		.image_index = 1,
	},
};

struct efi_capsule_update_info update_info = {
	.dfu_string = "mmc 0=u-boot.itb raw 0x4000 0x2000",
	.num_images = ARRAY_SIZE(fw_images),
	.images = fw_images,
};
#endif /* EFI_HAVE_CAPSULE_SUPPORT */

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
