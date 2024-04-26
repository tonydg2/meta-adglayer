#!/bin/sh
### BEGIN INIT INFO
# Provides:          hw-githash-boot
# Required-Start:    $remote_fs $syslog
# Required-Stop:     $remote_fs $syslog
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: Start hw-githash-boot at boot time
# Description:       Runs hw-githash-boot to read register values.
### END INIT INFO

case "$1" in
  start)
    echo "Starting hw-githash-boot"
    /usr/bin/hw-githash-boot
    ;;
  stop)
    echo "Stopping hw-githash-boot"
    ;;
  *)
    echo "Usage: /etc/init.d/hw-githash-boot {start|stop}"
    exit 1
    ;;
esac

exit 0
