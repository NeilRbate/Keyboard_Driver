PWD=${shell pwd}

obj-m += keyboard_driver.o

keyboard_driver-objs := src/main.o \
                        src/keyboard.o \
                        src/tools.o
                        
all:	
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	#echo 'ACTION=="add", SUBSYSTEM=="input", RUN+="/bin/bash $(PWD)/tools/load_driver.sh"' > $(PWD)/10-keyboarddriverloading.rules
	#echo 'ACTION=="remove", SUBSYSTEM=="input", RUN+="/bin/bash $(PWD)/tools/unload_driver.sh"' >> $(PWD)/10-keyboarddriverloading.rules
	#cp $(PWD)/10-keyboarddriverloading.rules /usr/lib/udev/rules.d/
	#udevadm control --reload-rules && udevadm trigger

clean:	
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	#rm /usr/lib/udev/rules.d/10-keyboarddriverloading.rules 
	#rm $(PWD)/10-keyboarddriverloading.rules 
	#udevadm control --reload-rules && udevadm trigger
