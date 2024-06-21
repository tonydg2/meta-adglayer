require factest.inc

SUMMARY = "Factory Acceptance Tests scripts"

COMPATIBLE_MACHINE = "zub1cg-sbc|mz-iocc|u96v2-sbc-factest"
RCONFLICTS:${PN} = "blinky"

# common factest source files for all machines
SRC_URI = "\
	file://factest.sh \
	file://buttons_and_leds_test.sh;subdir=${SCRIPT_LOC} \
	"

# source files specific to the u96v2-sbc-factest machine
SRC_URI:append:u96v2-sbc-factest = "\
	file://dp_test.sh;subdir=${SCRIPT_LOC}  \
	file://sd_test.sh;subdir=${SCRIPT_LOC}  \
	file://usb_host_test.sh;subdir=${SCRIPT_LOC}  \
	file://usb_device_test.sh;subdir=${SCRIPT_LOC}  \
	file://sensors_test.sh;subdir=${SCRIPT_LOC}  \
	file://loopback_gpios_test.sh;subdir=${SCRIPT_LOC}  \
	file://wifi_test.sh;subdir=${SCRIPT_LOC}  \
	file://bt_test.sh;subdir=${SCRIPT_LOC}  \
	"
