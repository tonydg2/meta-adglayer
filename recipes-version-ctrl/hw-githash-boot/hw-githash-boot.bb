DESCRIPTION = "Hardware Git Hash Boot Application"
LICENSE = "CLOSED"

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI =  "file://hw-githash-boot.c \
            file://hw-githash-boot.service "

inherit systemd

do_compile() {
    ${CC} ${CFLAGS} ${LDFLAGS} -o hw-githash-boot ${WORKDIR}/hw-githash-boot.c
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 hw-githash-boot ${D}${bindir}

    # Install the systemd service file
    install -d ${D}${systemd_system_unitdir}
    install -m 0644 ${WORKDIR}/hw-githash-boot.service ${D}${systemd_system_unitdir}/hw-githash-boot.service

    # Create the multi-user.target.wants directory if it does not exist
    install -d ${D}${systemd_system_unitdir}/multi-user.target.wants

    # Create the symbolic link
    ln -sf ${systemd_system_unitdir}/hw-githash-boot.service ${D}${systemd_system_unitdir}/multi-user.target.wants/hw-githash-boot.service
}

FILES:${PN} += "${bindir}/hw-githash-boot"
FILES:${PN} += "${systemd_system_unitdir}/*"

SYSTEMD_SERVICE:${PN} = "hw-githash-boot.service"
