DESCRIPTION = "Installs hw-githash-boot and its init script"
LICENSE = "CLOSED"

SRC_URI = "file://hw-githash-boot.c \
           file://hw-githash-boot.sh"

S = "${WORKDIR}"

do_compile() {
    ${CC} ${CFLAGS} ${LDFLAGS} hw-githash-boot.c -o hw-githash-boot
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${S}/hw-githash-boot ${D}${bindir}/hw-githash-boot

    install -d ${D}${sysconfdir}/init.d
    install -m 0755 ${WORKDIR}/hw-githash-boot.sh ${D}${sysconfdir}/init.d/hw-githash-boot

    # Ensure the rc5.d directory exists
    install -d ${D}${sysconfdir}/rc5.d

    # Create symbolic links for startup and shutdown
    #ln -sf ../init.d/hw-githash-boot ${D}${sysconfdir}/rc5.d/S01hw-githash-boot  # Early in boot
    ln -sf ../init.d/hw-githash-boot ${D}${sysconfdir}/rc5.d/S99hw-githash-boot  # Late in boot
}


FILES_${PN} += "${bindir}/hw-githash-boot \
                ${sysconfdir}/init.d/hw-githash-boot"


#ALLOW_EMPTY:${PN} = "1"

#pkg_postinst_ontarget:${PN}() {
#    # This will always run on the target, even during rootfs construction
#    update-rc.d hw-githash-boot defaults
#    update-rc.d hw-githash-boot enable
#}
