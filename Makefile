obj-m += keyboard_driver.o

keyboard_driver-objs := src/main.o \
                        src/keyboard.o \
                        src/tools.o
                        
all:	
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	insmod keyboard_driver.ko

clean:	
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rmmod keyboard_driver
