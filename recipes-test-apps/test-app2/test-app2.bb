LICENSE = "CLOSED"
LIC_FILES_CHKSUM = ""
SRC_URI = "file://test-app2.c	   file://Makefile	  "
S = "${WORKDIR}"

do_compile () {
	oe_runmake
}

do_install () {
	oe_runmake install DESTDIR=${D} BINDIR=${bindir}
}
