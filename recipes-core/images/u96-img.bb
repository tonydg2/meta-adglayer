DESCRIPTION = "u96 image"

require recipes-core/images/petalinux-image-minimal.bb

IMAGE_INSTALL:append = " \
 testapp1\
 test-app2\
 peekpoke\
 hw-githash-test\
 hw-githash\
 sw-timestamp\
 hw-githash-boot\
 ultra96-ap-setup\
 ultra96-misc\
 ultra96-radio-leds\
 ultra96-wpa\
 usb-gadget-ethernet\
 wilc3000-fw\
 wilc\
 ultra96-ap-setup\
 ultra96-startup-pages\
 ultra96-wlan0-config\
 iw\
 wifi-udp\
 ap1302\
 device-tree\
 camera-setup\
 run-camera\
 libdrm\
 libdrm-tests\
 vim\
 v4l-utils\
 packagegroup-petalinux-gstreamer\
 util-linux-mount\
 libpython3\
 packagegroup-petalinux-python-modules\
 python3\
 python3-core\
 python3-modules\
"
## remove dma stuff testing dual cam mezz
# dma-proxy
# dma-proxy-test
# mcdma-test
# mcdma-custom



# kernel headers:
#kernel-devsrc

# gcc and make tools:
#EXTRA_IMAGE_FEATURES:append= " tools-sdk"


IMAGE_INSTALL:remove = " \
 htop\
 iperf3\
 meson\
 libdfx\
 openamp-fw-echo-testd\
 openamp-fw-mat-muld\
 openamp-fw-rpc-demo\
 nfs-utils\
 nfs-utils-client\
"

