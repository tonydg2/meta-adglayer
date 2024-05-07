
#do_install:append() {
#    echo "Creating sshd_not_to_be_run to disable auto-start of SSHD"
#    install -d ${D}${sysconfdir}/ssh  # Ensure the directory /etc/ssh exists
#    touch ${D}${sysconfdir}/ssh/sshd_not_to_be_run  # Create the file in the correct location
#}


python() {
    machine = d.getVar('MACHINE')
    if machine == 'myhardware-zc702-zynq':
        # Define the additional commands for do_install task
        extra_install_commands = 'echo "Creating sshd_not_to_be_run to disable auto-start of SSHD";' \
                                 'install -d ${D}${sysconfdir}/ssh;' \
                                 'touch ${D}${sysconfdir}/ssh/sshd_not_to_be_run;'
        
        # Append the extra commands to the do_install task
        d.appendVar('do_install', extra_install_commands)
}

