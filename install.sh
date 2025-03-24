sudo ../rkdeveloptool/rkdeveloptool db ../rk3588_spl_loader_v1.15.113.bin
sleep 2
#sudo ../rkdeveloptool/rkdeveloptool gpt ../firmware/parameter.txt
#sleep 2
sudo ../rkdeveloptool/rkdeveloptool wl 0x4000 u-boot.itb
sleep 2
sudo ../rkdeveloptool/rkdeveloptool rd
