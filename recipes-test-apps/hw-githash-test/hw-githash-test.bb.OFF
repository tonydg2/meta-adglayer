LICENSE = "CLOSED"
LIC_FILES_CHKSUM = ""
SRC_URI = "file://hw-githash-test.c	   file://Makefile	  "
S = "${WORKDIR}"

COMPATIBLE_MACHINE = "(myhardware-zc702-zynq|myhardware-u96v2-zynqmp|u96-avnet|hw-u96)"


do_configure:prepend() {
    cfg_file=${B}/hw-githash-test.h
    echo "Creating configuration header at ${cfg_file}"
    
    echo "#ifndef HW_GITHASH_CONFIG_H" > ${cfg_file}
    echo "#define HW_GITHASH_CONFIG_H" >> ${cfg_file}

    case "${MACHINE}" in
        myhardware-zc702-zynq)
            echo "#define BASE_ADDR 0x40000000" >> ${cfg_file}
            ;;
        myhardware-u96v2-zynqmp | hw-u96)
            echo "#define BASE_ADDR 0xA0012000" >> ${cfg_file}
            ;;
        *)
            echo "#error Unsupported MACHINE" >> ${cfg_file}
            exit 1
            ;;
    esac

    echo "#endif /* HW_GITHASH_CONFIG_H */" >> ${cfg_file}
}

do_compile () {
	oe_runmake
}

do_install () {
	oe_runmake install DESTDIR=${D} BINDIR=${bindir}
}

#do_clean:append() {
#    rm -f ${B}/hw-githash-test.h
#}
