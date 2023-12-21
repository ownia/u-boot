// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2023 Rockchip Electronics Co,. Ltd.
 */

#include <efi_loader.h>
#include <fdtdec.h>
#include <fdt_support.h>

#define ROCKCHIP_UPDATABLE_IMAGES 1

#if IS_ENABLED(CONFIG_EFI_HAVE_CAPSULE_SUPPORT)
struct efi_fw_image fw_images[ROCKCHIP_UPDATABLE_IMAGES] = {0};

struct efi_capsule_update_info update_info = {
	.dfu_string = "mmc 0=u-boot.itb raw 0x4000 0x2000",
	.num_images = ROCKCHIP_UPDATABLE_IMAGES,
	.images = fw_images,
};

void rockchip_capsule_update_board_setup(void)
{
	efi_guid_t uboot_image_type_guid = ROCKCHIP_UBOOT_IMAGE_GUID;

	guidcpy(&fw_images[0].image_type_id, &uboot_image_type_guid);
	fw_images[0].fw_name = u"ROCKCHIP_UBOOT";
}
#endif /* EFI_HAVE_CAPSULE_SUPPORT */

#ifdef CONFIG_OF_BOARD_SETUP
static int rk3588_add_reserved_memory_fdt_nodes(void *new_blob)
{
	struct fdt_memory gap1 = {
		.start = 0x3fc000000,
		.end = 0x3fc4fffff,
	};
	struct fdt_memory gap2 = {
		.start = 0x3fff00000,
		.end = 0x3ffffffff,
	};
	unsigned long flags = FDTDEC_RESERVED_MEMORY_NO_MAP;
	unsigned int ret;

	/*
	 * Inject the reserved-memory nodes into the DTS
	 */
	ret = fdtdec_add_reserved_memory(new_blob, "gap1", &gap1,  NULL, 0,
					 NULL, flags);
	if (ret)
		return ret;

	return fdtdec_add_reserved_memory(new_blob, "gap2", &gap2,  NULL, 0,
					  NULL, flags);
}

int ft_board_setup(void *blob, struct bd_info *bd)
{
	return rk3588_add_reserved_memory_fdt_nodes(blob);
}
#endif
