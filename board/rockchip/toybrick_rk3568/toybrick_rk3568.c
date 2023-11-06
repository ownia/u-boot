// SPDX-License-Identifier: GPL-2.0+
/*
 * Weizhao Ouyang <weizhao.ouyang@arm.com>
 */

#include <common.h>
#include <efi_loader.h>

#define TB_RK3568X0_IDBLOADER_IMAGE_GUID \
	EFI_GUID(0xa2d37d82, 0x51e0, 0x420d, 0x83, 0xf5, \
		 0x47, 0x0d, 0xb9, 0x93, 0xdd, 0x35)

#define TB_RK3568X0_UBOOT_IMAGE_GUID \
	EFI_GUID(0x5a30833f, 0x8c43, 0x47b1, 0xa4, 0x1b, \
		 0x84, 0xd4, 0x08, 0x83, 0xd0, 0xc6)

#define TOYBRICK_UPDATABLE_IMAGES 2

#if IS_ENABLED(CONFIG_EFI_HAVE_CAPSULE_SUPPORT)
static struct efi_fw_image fw_images[TOYBRICK_UPDATABLE_IMAGES] = {0};

struct efi_capsule_update_info update_info = {
	.num_images = TOYBRICK_UPDATABLE_IMAGES,
	.images = fw_images,
};

#ifndef CONFIG_SPL_BUILD
void rockchip_capsule_update_board_setup(void)
{
	efi_guid_t idbldr_image_type_guid = TB_RK3568X0_IDBLOADER_IMAGE_GUID;
	efi_guid_t uboot_image_type_guid = TB_RK3568X0_UBOOT_IMAGE_GUID;

	guidcpy(&fw_images[0].image_type_id, &idbldr_image_type_guid);
	guidcpy(&fw_images[1].image_type_id, &uboot_image_type_guid);

	fw_images[0].fw_name = u"TB-RK3568X0-IDBLOADER";
	fw_images[1].fw_name = u"TB-RK3568X0-UBOOT";
}
#endif
#endif
