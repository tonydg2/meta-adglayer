LICENSE = "CLOSED"
LIC_FILES_CHKSUM = ""

python() {
    machine = d.getVar('MACHINE')
    if machine == 'myhardware-zc702-zynq':
        # Append the custom interfaces file for zc702
        d.appendVar('SRC_URI', ' file://interfaces')
}

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
