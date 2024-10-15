export ROCKCHIP_TPL=../firmware/rk3588_ddr_lp4_2112MHz_lp5_2400MHz_v1.16.bin
export BL31=../arm-trusted-firmware/build/rk3588/release/bl31/bl31.elf
export TEE=../firmware/tee.bin

if [ "$1" == "toybrick" ];
then
	make CROSS_COMPILE=aarch64-linux-gnu- toybrick-rk3588_defconfig
	make CROSS_COMPILE=aarch64-linux-gnu- -j16
fi

if [ "$1" == "armsom" ];
then
	make CROSS_COMPILE=aarch64-linux-gnu- sige7-rk3588_defconfig
	make CROSS_COMPILE=aarch64-linux-gnu- -j16
fi

# Note:
# update CRT files
