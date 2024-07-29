LICENSE = "CLOSED"

inherit module

SRC_URI = "file://mcdma-test.c \
           file://Makefile"

S = "${WORKDIR}"

# The inherit of module.bbclass will automatically name module packages with
# "kernel-module-" prefix as required by the oe-core build environment.

#KERNEL_MODULE_AUTOLOAD += "mcdma-test"

