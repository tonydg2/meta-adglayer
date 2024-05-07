COMPATIBLE_MACHINE = "(myhardware-zc702-zynq|myhardware-u96v2-zynqmp)"

DESCRIPTION = "Create a timestamp file in /etc"
LICENSE = "CLOSED"

do_install() {
    echo "Generating sw-timestamp"
    install -d ${D}/etc
    echo $(date -u +%Y%m%d%H%M%S) > ${D}/etc/sw-timestamp
}

FILES_${PN} += "/etc/sw-timestamp"

inherit allarch
