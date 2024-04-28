mkimage -f test.its tests.itb

#openssl req -x509 -sha256 -newkey rsa:2048 -subj /CN=CRT/ \
#	-keyout CRT.key -out CRT.crt -nodes -days 365
#cert-to-efi-sig-list CRT.crt CRT.esl

./tools/mkeficapsule \
	--private-key "CRT.key" \
	--certificate "CRT.crt" \
	--guid 5452a04a-462d-4433-9778-2b5259277bb3 \
	--index 1 \
	"tests.itb" \
	"capsule1.bin"

/home/weiouy01/code/systemready-scripts/capsule-tool.py \
	--de-authenticate --output unauth.bin capsule1.bin

/home/weiouy01/code/systemready-scripts/capsule-tool.py \
	--tamper --output tampered.bin capsule1.bin
