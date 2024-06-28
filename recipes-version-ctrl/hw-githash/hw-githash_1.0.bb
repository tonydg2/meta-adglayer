DESCRIPTION = "FPGA HW Git Hash Application"
LICENSE = "CLOSED"
LIC_FILES_CHKSUM = ""
SRC_URI = "file://hw-githash.c \
           file://hw-githash.service \
           file://Makefile \
          "

S = "${WORKDIR}"
CFLAGS:prepend = "-I ${S}/include"
do_compile () {
	oe_runmake
}

inherit systemd

do_install() {
    install -d ${D}${bindir}
    install -m 0755 hw-githash ${D}${bindir}
    install -d ${D}${systemd_system_unitdir}
    install -m 0644 ${WORKDIR}/hw-githash.service ${D}${systemd_system_unitdir}
}

SYSTEMD_SERVICE:${PN} = "hw-githash.service"
FILES:${PN} += "${systemd_system_unitdir}/hw-githash.service"

