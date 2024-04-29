DESCRIPTION = "ADG custom image zc702"

COMPATIBLE_MACHINE = "myhardware-zc702-zynq"
EXPECTED_MACHINE = "myhardware-zc702-zynq"

python() {
    if d.getVar('MACHINE') != d.getVar('EXPECTED_MACHINE'):
        raise bb.parse.SkipPackage("This image recipe is intended only for machine type %s, but MACHINE is set to %s." % (d.getVar('EXPECTED_MACHINE'), d.getVar('MACHINE')))
}

#inherit petalinux-image-minimal

# this works but not sure if correct, inherit above doesn't work
require recipes-core/images/petalinux-image-minimal.bb

IMAGE_INSTALL:append = " peekpoke"

IMAGE_INSTALL:append = " sw-timestamp"
#IMAGE_INSTALL:append = " hw-githash"
IMAGE_INSTALL:append = " hw-githash-test"
IMAGE_INSTALL:append = " hw-githash-boot"
IMAGE_INSTALL:append = " testapp1 test-app2"

#SYSTEMD_AUTO_ENABLE = "enable"
#SYSTEMD_SERVICE_${PN} = "hw-githash.service"
