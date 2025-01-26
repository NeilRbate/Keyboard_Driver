!#/usr/bin/bash
echo "Keyboard unpluged"

rmmod keyboard_driver
echo -n "1-3:1.0" > /sys/bus/usb/drivers/my_keyboard_driver/unbind
echo -n "1-3:1.0" > /sys/bus/usb/drivers/usbhid/bind
