// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2016 Rockchip Electronics Co., Ltd
 */

#include <dm.h>
#include <mmc.h>
#include <part.h>
#include <efi_loader.h>

#define ROCKPI4_UPDATABLE_IMAGES	2

#if IS_ENABLED(CONFIG_EFI_HAVE_CAPSULE_SUPPORT) && IS_ENABLED(CONFIG_EFI_PARTITION)

#define DFU_ALT_BUF_LEN			SZ_1K

static struct efi_fw_image *fw_images = {0};
static struct efi_fw_image fw_images_d[ROCKPI4_UPDATABLE_IMAGES] = {0};

struct efi_capsule_update_info update_info = {
	.num_images = ROCKPI4_UPDATABLE_IMAGES,
	.images = fw_images_d,
};

static bool updatable_image(struct disk_partition *info)
{
	int i;
	bool ret = false;
	efi_guid_t image_type_guid;

	uuid_str_to_bin(info->type_guid, image_type_guid.b,
			UUID_STR_FORMAT_GUID);

	for (i = 0; i < update_info.num_images; i++) {
		if (!guidcmp(&fw_images[i].image_type_id, &image_type_guid)) {
			ret = true;
			break;
		}
	}

	return ret;
}

static void set_image_index(struct disk_partition *info, int index)
{
	int i;
	efi_guid_t image_type_guid;

	uuid_str_to_bin(info->type_guid, image_type_guid.b,
			UUID_STR_FORMAT_GUID);

	for (i = 0; i < update_info.num_images; i++) {
		if (!guidcmp(&fw_images[i].image_type_id, &image_type_guid)) {
			fw_images[i].image_index = index;
			break;
		}
	}
}

static int get_mmc_desc(struct blk_desc **desc)
{
	int ret;
	struct mmc *mmc;
	struct udevice *dev;

	/*
	 * For now the firmware images are assumed to
	 * be on the SD card
	 */
	ret = uclass_get_device(UCLASS_MMC, 1, &dev);
	if (ret)
		return -1;

	mmc = mmc_get_mmc_dev(dev);
	if (!mmc)
		return -ENODEV;

	if ((ret = mmc_init(mmc)))
		return ret;

	*desc = mmc_get_blk_desc(mmc);
	if (!*desc)
		return -1;

	return 0;
}

void set_dfu_alt_info(char *interface, char *devstr)
{
	const char *name;
	bool first = true;
	int p, len, devnum, ret;
	char buf[DFU_ALT_BUF_LEN];
	struct disk_partition info;
	struct blk_desc *desc = NULL;

	ret = get_mmc_desc(&desc);
	if (ret) {
		log_err("Unable to get mmc desc\n");
		return;
	}

	memset(buf, 0, sizeof(buf));
	name = blk_get_uclass_name(desc->uclass_id);
	devnum = desc->devnum;
	len = strlen(buf);

	len += snprintf(buf + len, DFU_ALT_BUF_LEN - len,
			 "%s %d=", name, devnum);

	for (p = 1; p <= MAX_SEARCH_PARTITIONS; p++) {
		if (part_get_info(desc, p, &info))
			continue;

		/* Add entry to dfu_alt_info only for updatable images */
		if (updatable_image(&info)) {
			if (!first)
				len += snprintf(buf + len,
						DFU_ALT_BUF_LEN - len, ";");

			len += snprintf(buf + len, DFU_ALT_BUF_LEN - len,
					"%s%d_%s part %d %d",
					name, devnum, info.name, devnum, p);
			first = false;
		}
	}

	log_debug("dfu_alt_info => %s\n", buf);
	env_set("dfu_alt_info", buf);
}

static bool board_is_rockpi_4b(void)
{
	return of_machine_is_compatible("radxa,rockpi4b");
}

static bool board_is_rockpi_4c(void)
{
	return of_machine_is_compatible("radxa,rockpi4c");
}

void rockchip_capsule_update_board_setup(void)
{
	if (board_is_rockpi_4b()) {
		efi_guid_t idbldr_image_type_guid =
			ROCKPI_4B_IDBLOADER_IMAGE_GUID;
		efi_guid_t uboot_image_type_guid = ROCKPI_4B_UBOOT_IMAGE_GUID;

		guidcpy(&fw_images[0].image_type_id, &idbldr_image_type_guid);
		guidcpy(&fw_images[1].image_type_id, &uboot_image_type_guid);

		fw_images[0].fw_name = u"ROCKPI4B-IDBLOADER";
		fw_images[1].fw_name = u"ROCKPI4B-UBOOT";
	} else if (board_is_rockpi_4c()) {
		efi_guid_t idbldr_image_type_guid =
			ROCKPI_4C_IDBLOADER_IMAGE_GUID;
		efi_guid_t uboot_image_type_guid = ROCKPI_4C_UBOOT_IMAGE_GUID;

		guidcpy(&fw_images[0].image_type_id, &idbldr_image_type_guid);
		guidcpy(&fw_images[1].image_type_id, &uboot_image_type_guid);

		fw_images[0].fw_name = u"ROCKPI4C-IDBLOADER";
		fw_images[1].fw_name = u"ROCKPI4C-UBOOT";
	}
}

static void gpt_capsule_update_setup(void)
{
	int p, i, ret;
	struct disk_partition info;
	struct blk_desc *desc = NULL;

	fw_images = update_info.images;
	rockchip_capsule_update_board_setup();

	ret = get_mmc_desc(&desc);
	if (ret) {
		log_err("Unable to get mmc desc\n");
		return;
	}

	for (p = 1, i = 1; p <= MAX_SEARCH_PARTITIONS; p++) {
		if (part_get_info(desc, p, &info))
			continue;

		/*
		 * Since we have a GPT partitioned device, the updatable
		 * images could be stored in any order. Populate the
		 * image_index at runtime.
		 */
		if (updatable_image(&info)) {
			set_image_index(&info, i);
			i++;
		}
	}
}
#endif /* CONFIG_EFI_HAVE_CAPSULE_SUPPORT && CONFIG_EFI_PARTITION */

int rk_board_late_init(void)
{
#if IS_ENABLED(CONFIG_EFI_HAVE_CAPSULE_SUPPORT) && IS_ENABLED(CONFIG_EFI_PARTITION)
	gpt_capsule_update_setup();
#endif

	return 0;
}

