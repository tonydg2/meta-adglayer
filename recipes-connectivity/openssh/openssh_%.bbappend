do_install:append() {
    echo "Creating sshd_not_to_be_run to disable auto-start of SSHD"
    install -d ${D}${sysconfdir}/ssh  # Ensure the directory /etc/ssh exists
    touch ${D}${sysconfdir}/ssh/sshd_not_to_be_run  # Create the file in the correct location
}