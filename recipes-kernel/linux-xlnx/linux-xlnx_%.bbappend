COMPATIBLE_MACHINE = "(myhardware-zc702-zynq|myhardware-u96v2-zynqmp)"

FILESEXTRAPATHS:prepend := "${THISDIR}/linux-xlnx:"


#SRC_URI += "file://tuners.cfg \
#            file://dvb-frontends.cfg \
#            file://media-spi.cfg \
#            "

#python() {
#    machine = d.getVar('MACHINE')
#    if machine == 'myhardware-u96v2-zynqmp':
#        d.appendVar('SRC_URI', ' file://u96.cfg')
#}

python() {
    machine = d.getVar('MACHINE')
    if machine == 'myhardware-u96v2-zynqmp':
        d.appendVar('SRC_URI', ' file://u96.cfg')
    elif machine == 'myhardware-zc702-zynq':
        d.appendVar('SRC_URI', ' file://zc702.cfg')
}