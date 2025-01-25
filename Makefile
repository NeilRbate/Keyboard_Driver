obj-m += keyboard_driver.o

keyboard_driver-objs := src/main.o \
                        src/keyboard.o \
                        src/tools.o
                        
all:	
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:	
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rmmod keyboard_driver
