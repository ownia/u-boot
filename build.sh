export ROCKCHIP_TPL=../rkbin/bin/rk35/rk3588_ddr_lp4_2112MHz_lp5_2736MHz_v1.12.bin 
export BL31=../trusted-firmware-a/build/rk3588/release/bl31/bl31.elf
#export BL31=../rkbin/bin/rk35/rk3588_bl31_v1.40.elf
export TEE=../rkbin/bin/rk35/rk3588_bl32_v1.13.bin

make CROSS_COMPILE=aarch64-linux-gnu- toybrick-rk3588_defconfig
make CROSS_COMPILE=aarch64-linux-gnu- -j4

# Note:
# update CRT files
