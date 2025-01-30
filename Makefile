PWD=${shell pwd}

obj-m += keyboard_driver.o

keyboard_driver-objs := src/main.o \
                        src/keyboard.o \
                        src/keyboard_helpers.o \
			src/list.o \
			src/misc_module.o \
			src/log.o
                        
all:	
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	echo 'ACTION=="add", SUBSYSTEM=="input", KERNELS=="1-3:1.1",  RUN+="/usr/bin/bash $(PWD)/tools/load_driver.sh"' > $(PWD)/10-keyboard_driver.rules
	echo 'ACTION=="remove", SUBSYSTEM=="input" KERNELS=="1-3:1.1" , RUN+="/usr/sbin/rmmod keyboard_driver"' >> $(PWD)/10-keyboard_driver.rules
	echo '!#/usr/bin/bash' > tools/load_driver.sh
	echo 'echo "Keyboard plugged"' >>tools/load_driver.sh
	echo 'insmod $(PWD)/keyboard_driver.ko' >> tools/load_driver.sh
	echo 'echo -n "1-3:1.0" > /sys/bus/usb/drivers/usbhid/unbind' >> tools/load_driver.sh
	echo 'echo -n "1-3:1.0" > /sys/bus/usb/drivers/my_keyboard_driver/bind' >> tools/load_driver.sh 
	cp $(PWD)/10-keyboard_driver.rules /usr/lib/udev/rules.d/
	udevadm control --reload-rules && udevadm trigger

clean:	
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm /usr/lib/udev/rules.d/10-keyboard_driver.rules 
	rm $(PWD)/10-keyboard_driver.rules 
	udevadm control --reload-rules && udevadm trigger

re: clean all
