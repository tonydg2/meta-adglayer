# see main recipe u-boot-xlnx-scr. 
# this adds only my custom boot.cmd.u96 file. The "+=" for the SRC_URI is necessary or it will fail

BOOTMODE = "u96"

SRC_URI += " \
    file://boot.cmd.u96 \
    "

FILESEXTRAPATHS:prepend := "${THISDIR}/u-boot-xlnx-scr:"
