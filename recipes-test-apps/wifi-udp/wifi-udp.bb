# run wifi.sh on booted u96 first, located in ultra96-misc recipe 

LICENSE = "CLOSED"

SRC_URI += " \
	    file://udp_listener.py \
	    file://udp_sender.py \
	    file://udp_sender2.py \
"

do_install() {
	install -d ${D}/home/root/
	install -m 755 ${WORKDIR}/udp_listener.py ${D}/home/root/
	install -m 755 ${WORKDIR}/udp_sender.py ${D}/home/root/
	install -m 755 ${WORKDIR}/udp_sender2.py ${D}/home/root/
}

FILES:${PN} = " \
		/home/root/udp_listener.py \
		/home/root/udp_sender.py \
		/home/root/udp_sender2.py \
"
