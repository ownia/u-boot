# SPDX-License-Identifier: GPL-2.0+

dtb-$(CONFIG_TARGET_AXS101) +=  axs101.dtb
dtb-$(CONFIG_TARGET_AXS103) +=  axs103.dtb
dtb-$(CONFIG_TARGET_NSIM) +=  nsim.dtb
dtb-$(CONFIG_TARGET_TB100) +=  abilis_tb100.dtb
dtb-$(CONFIG_TARGET_EMSDP) +=  emsdp.dtb
dtb-$(CONFIG_TARGET_HSDK) +=  hsdk.dtb hsdk-4xd.dtb
dtb-$(CONFIG_TARGET_IOT_DEVKIT) +=  iot_devkit.dtb

include $(srctree)/scripts/Makefile.dts

# Add any required device tree compiler flags here
DTC_FLAGS += -R 4
