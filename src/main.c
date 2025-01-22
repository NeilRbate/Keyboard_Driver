#include "../include/include.h"

static void keyboard_disconnect(struct usb_interface *interface);
static int keyboard_probe(struct usb_interface *interface, const struct usb_device_id *id);

struct usb_keyboard {
    struct usb_device *udev;
    struct input_dev *input;
};

static struct usb_driver keyboard_driver = {
	.name = "my_keyboard_driver",
	.probe = keyboard_probe,
	.disconnect = keyboard_disconnect,
	.id_table = keyboard_table,
};

MODULE_DEVICE_TABLE (usb, keyboard_table);

static int keyboard_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
	struct input_dev 	*input_device;
	struct usb_keyboard	*keyboard;
	int 			result;

	keyboard = kzalloc(sizeof(struct usb_keyboard), GFP_KERNEL);
	if (!keyboard)
		return -ENOMEM;

	keyboard->udev = usb_get_dev(interface_to_usbdev(interface));

	input_device = input_allocate_device();
	if (!input_device) {
		pr_err("input_allocate_device failed");
		kfree(keyboard);
		return -ENOMEM;
	}

	input_device->name = "My keyboard";
	input_device->phys = "usbkbd/input0";
	input_device->id.bustype = BUS_USB;
	input_device->evbit[0] = BIT(EV_KEY) | BIT(EV_SYN);
	//Example, to change
	input_device->keybit[BIT_WORD(KEY_A)] = BIT(KEY_A) | BIT(KEY_B);

	//set_bit(KEY_A, input_device->keybit);
    	//set_bit(KEY_B, input_device->keybit);

	result = input_register_device(input_device);
	if (result) {
		pr_err("input_register_device failed");
		input_free_device(input_device);
		kfree(keyboard);
		return result;
	}

	keyboard->input = input_device;
	usb_set_intfdata(interface, keyboard);
	pr_debug("keyboard_probe is alive");
	//Todo Check return value
	
	return 0;
}

static void keyboard_disconnect(struct usb_interface *interface) 
{
	struct usb_keyboard	*keyboard;

	keyboard = usb_get_intfdata(interface);
	input_unregister_device(keyboard->input);
	kfree(keyboard);
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
