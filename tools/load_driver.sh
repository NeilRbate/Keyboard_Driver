!#/usr/bin/bash
echo "Keyboard plugged"
insmod /root/Keyboard_Driver/keyboard_driver.ko
echo -n "1-3:1.0" > /sys/bus/usb/drivers/usbhid/unbind
echo -n "1-3:1.0" > /sys/bus/usb/drivers/my_keyboard_driver/bind
