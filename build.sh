export ROCKCHIP_TPL=../../rk3588/rkbin/bin/rk35/rk3588_ddr_lp4_2112MHz_lp5_2736MHz_v1.12.bin
export BL31=../../rk3588/rkbin/bin/rk35/rk3588_bl31_v1.40.elf
export TEE=../../rk3588/rkbin/bin/rk35/rk3588_bl32_v1.13.bin
make CROSS_COMPILE=aarch64-linux-gnu- armsom-rk3588_defconfig
make CROSS_COMPILE=aarch64-linux-gnu- -j4

# # Note:
# # update CRT files

