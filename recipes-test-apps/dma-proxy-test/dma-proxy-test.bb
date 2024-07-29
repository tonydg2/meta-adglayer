LICENSE = "CLOSED"

SRC_URI = " \
	file://dma-proxy-test.c \
	file://dma-proxy.h \
	file://Makefile \
"

S = "${WORKDIR}"

DEPENDS = "dma-proxy"

CFLAGS += "-pthread"
LDFLAGS += "-lpthread"

EXTRA_OEMAKE = "'CFLAGS=${CFLAGS}' 'LDFLAGS=${LDFLAGS}'"

do_compile() {
  oe_runmake
}

do_install() {
  install -d ${D}${bindir}
  install -m 0755 dma-proxy-test ${D}${bindir}
}
