# this file works if named explicitly: base-files_3.0.14.bbappend


FILESEXTRAPATHS:prepend  := "${THISDIR}/files:"

SRC_URI += "file://dot.bashrc"

do_install:append () {
	install -m 0755 ${WORKDIR}/dot.bashrc ${D}${sysconfdir}/skel/.bashrc
}

