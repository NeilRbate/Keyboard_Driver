#include "../include/include.h"

static void keyboard_disconnect(struct usb_interface *interface);
static int keyboard_probe(struct usb_interface *interface, const struct usb_device_id *id);

static struct usb_driver keyboard_driver = {
	.name = "my_keyboard_driver",
	.probe = keyboard_probe,
	.disconnect = keyboard_disconnect,
	.id_table = keyboard_table,
};

MODULE_DEVICE_TABLE (usb, keyboard_table);

static int keyboard_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
	struct input_dev *input_device;
	int result;

	input_device = input_allocate_device();
	if (!input_device) {
		pr_err("input_allocate_device failed");
		return -ENOMEM;
	}

	input_device->name = "My keyboard";
	input_device->phys = "usbkbd/input0";
	input_device->id.bustype = BUS_USB;
	input_device->evbit[0] = BIT(EV_KEY) | BIT(EV_SYN);

	set_bit(KEY_A, input_device->keybit);
    	set_bit(KEY_B, input_device->keybit);

	result = input_register_device(input_device);
	if (result) {
		pr_err("input_register_device failed");
		input_free_device(input_device);
		return result;
	}
	pr_debug("keyboard_probe is alive");
	//Todo Check return value
	
	return 0;
}

static void keyboard_disconnect(struct usb_interface *interface) 
{
    printk(KERN_INFO "Keyboard disconnected\n");
}

static int __init keyboard_driver_init(void)
{
	pr_info("Init module\n");

	int result;

	result = usb_register(&keyboard_driver);
	if (result) {
		pr_err("usb_register for %s failed. Error number %d\n",
				keyboard_driver.name, result);
		return result;
	}

	return 0;
}

static void __exit keyboard_driver_exit(void)
{
	usb_deregister(&keyboard_driver);
	pr_info("Exit module\n");
}

module_init(keyboard_driver_init);
module_exit(keyboard_driver_exit);
