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
 dma-proxy\
 dma-proxy-test\
 mcdma-test\
"
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

