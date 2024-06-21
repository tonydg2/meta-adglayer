FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += "file://avnet-bsp.cfg \
            file://vitis_kconfig.cfg \
            file://0001-hwmon-pmbus-Add-support-Infineon-IR38062-IR38063.patch \
            "

SRC_URI:append:u96v2-sbc = " file://fix_u96v2_pwrseq_simple.patch \
                           "

