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
"