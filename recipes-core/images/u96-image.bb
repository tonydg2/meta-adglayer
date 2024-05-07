DESCRIPTION = "ADG custom image ultra96v2"

COMPATIBLE_MACHINE = "myhardware-u96v2-zynqmp"
EXPECTED_MACHINE = "myhardware-u96v2-zynqmp"

python() {
    if d.getVar('MACHINE') != d.getVar('EXPECTED_MACHINE'):
        raise bb.parse.SkipPackage("This image recipe is intended only for machine type %s, but MACHINE is set to %s." % (d.getVar('EXPECTED_MACHINE'), d.getVar('MACHINE')))
}

#inherit petalinux-image-minimal

# this works but not sure if correct, inherit above doesn't work
#require recipes-core/images/avnet-image-minimal.bb
require recipes-core/images/petalinux-image-minimal.bb

IMAGE_INSTALL:append = " testapp1 test-app2"
IMAGE_INSTALL:append = " peekpoke"
IMAGE_INSTALL:append = " hw-githash-test"

# need to do this for systemd instead (at recipe)
#IMAGE_INSTALL:append = " hw-githash-boot"

