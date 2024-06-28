#COMPATIBLE_MACHINE = "(myhardware-zc702-zynq|myhardware-u96v2-zynqmp|u96-avnet)"

DESCRIPTION = "Create a timestamp file in /etc"
LICENSE = "CLOSED"

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
SRC_URI:append = "file://sw-timestamp.service"

inherit systemd

do_install() {
    echo "Generating sw-timestamp"
    install -d ${D}/etc
#    echo $(date -u +%Y%m%d%H%M%S) > ${D}/etc/sw-timestamp

    # initial line uses '>', subsequent appends are '>>'
    echo "-------------------------------------------------------------------------------" > ${D}/etc/sw-timestamp
    echo "*************** SW Image TIMESTAMP: $(date -u +%Y%m%d%H%M%S) ***********" >> ${D}/etc/sw-timestamp
    echo "-------------------------------------------------------------------------------" >> ${D}/etc/sw-timestamp


    # Install the systemd service file
    install -d ${D}${systemd_system_unitdir}
    install -m 0644 ${WORKDIR}/sw-timestamp.service ${D}${systemd_system_unitdir}/sw-timestamp.service

    # Create the multi-user.target.wants directory if it does not exist
    install -d ${D}${systemd_system_unitdir}/multi-user.target.wants

    # Create the symbolic link
    ln -sf ${systemd_system_unitdir}/sw-timestamp.service ${D}${systemd_system_unitdir}/multi-user.target.wants/sw-timestamp.service

}

FILES:${PN} += "/etc/sw-timestamp"
FILES:${PN} += "${systemd_system_unitdir}/*"
#FILES:${PN} += "${systemd_system_unitdir}/sw-timestamp.service"
#FILES:${PN} += "${systemd_system_unitdir}/multi-user.target.wants"
#FILES:${PN} += "${systemd_system_unitdir}/multi-user.target.wants/sw-timestamp.service"

#SYSTEMD_AUTO_ENABLE = "enable"
SYSTEMD_SERVICE:${PN} = "sw-timestamp.service"
