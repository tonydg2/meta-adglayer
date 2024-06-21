DESCRIPTION = "ADG custom image ultra96v2"

COMPATIBLE_MACHINE = "(myhardware-u96v2-zynqmp|u96-avnet|hw-u96)"

require recipes-core/images/petalinux-image-minimal.bb

IMAGE_INSTALL:append = " testapp1 test-app2"
IMAGE_INSTALL:append = " peekpoke"
IMAGE_INSTALL:append = " hw-githash-test"

# need to do this for systemd instead (at recipe)
#IMAGE_INSTALL:append = " hw-githash-boot"

## avnet
IMAGE_INSTALL:append = "\
 wilc3000-fw\
 wilc\
 "

IMAGE_INSTALL:append = "\
 e2fsprogs-mke2fs\
 run-postinsts\
 udev-extraconf\
 dosfstools\
 bc\
 bonnie++\
 cmake\
 coreutils\
 dnf\
 e2fsprogs\
 e2fsprogs-badblocks\
 e2fsprogs-e2fsck\
 e2fsprogs-resize2fs\
 ethtool\
 gpio-utils\
 hdparm\
 i2c-tools\
 i2c-tools-misc\
 json-c\
 libpython3\
 lmsensors-sensorsdetect\
 mesa-megadriver\
 nano\
 opencl-clhpp-dev\
 opencl-headers-dev\
 openssh\
 openssh-scp\
 openssh-sftp-server\
 openssh-sshd\
 packagegroup-petalinux-display-debug\
 packagegroup-petalinux-gstreamer\
 packagegroup-petalinux-lmsensors\
 packagegroup-petalinux-matchbox\
 packagegroup-petalinux-opencv\
 packagegroup-petalinux-opencv-dev\
 packagegroup-petalinux-python-modules\
 packagegroup-petalinux-self-hosted\
 packagegroup-petalinux-v4lutils\
 packagegroup-petalinux-x11\
 parted\
 pmic-prog\
 python3\
 python3-pip\
 python3-pyserial\
 usbutils\
 util-linux\
 util-linux-blkid\
 util-linux-fdisk\
 util-linux-mkfs\
 util-linux-mount\
 xrt\
 xrt-dev\
 zocl\
 bluez5\
 connman-gtk\
 git\
 iw\
 libftdi\
 openamp-fw-echo-testd\
 openamp-fw-mat-muld\
 openamp-fw-rpc-demo\
 packagegroup-petalinux\
 packagegroup-petalinux-96boards-sensors\
 packagegroup-petalinux-benchmarks\
 packagegroup-petalinux-openamp\
 packagegroup-petalinux-ultra96-webapp\
 packagegroup-petalinux-utils\
 ultra96-ap-setup\
 ultra96-misc\
 ultra96-radio-leds\
 ultra96-wpa\
 usb-gadget-ethernet\
 "

IMAGE_INSTALL:remove = "\
 "
