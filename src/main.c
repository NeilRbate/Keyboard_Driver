#include "../include/include.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Julien Barbate");
MODULE_DESCRIPTION("This is an USB keyboard device driver");

struct usb_device_id keyboard_table [] = {
        { USB_DEVICE(USB_KEYBOARD_VENDOR_ID, USB_KEYBOARD_PRODUCT_ID) },
        { }
};

struct usb_driver keyboard_driver = {
	.name = "my_keyboard_driver",
	.id_table = keyboard_table,
	.probe = keyboard_probe,
	.disconnect = keyboard_disconnect,
};

static int __init keyboard_driver_init(void)
{
	int res;

	res = usb_register(&keyboard_driver);
	if (res) {
		pr_err("usb_register for %s failed. Error number %d\n",
				keyboard_driver.name, res);
		return res;
	}

	pr_info("Custom keyboard driver is loaded !\n");

	return 0;
}

static void __exit keyboard_driver_exit(void)
{
	usb_deregister(&keyboard_driver);
	pr_info("Custom keyboard driver is unloaded\n");
}

module_init(keyboard_driver_init);
module_exit(keyboard_driver_exit);
