LICENSE = "CLOSED"
LIC_FILES_CHKSUM = ""
SRC_URI = "file://hw-githash-test.c	   file://Makefile	  "
S = "${WORKDIR}"

do_compile () {
	oe_runmake
}

do_install () {
	oe_runmake install DESTDIR=${D} BINDIR=${bindir}
}
