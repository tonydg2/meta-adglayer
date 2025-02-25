see meta-on-semiconductor layer
  copy run_camera.sh to meta-on-semiconductor layer
    *(or make a recipe append here...)



ADG notes:
Need symlink:
  ln -s /usr/lib/libpython3.10.so.1.0 /usr/lib/libpython3.10.so

disable display before run_camera so it's not in use:
  systemctl stop getty@tty1.service
  echo 0 > /sys/class/graphics/fbcon/cursor_blink

run camera 
  run_camera -s dp -w 1920 -h 1080
