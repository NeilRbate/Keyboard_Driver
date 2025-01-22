#include "../include/include.h"

static void keyboard_disconnect(struct usb_interface *interface);
static int keyboard_probe(struct usb_interface *interface, const struct usb_device_id *id);


struct usb_keyboard {
    struct usb_device *udev;
    struct input_dev *input;
    struct urb *irq_urb;  // URB for receiving HID reports
    unsigned char *irq_buf;  // Buffer for HID reports
};

// This function will parse the HID report and send key events
static int parse_hid_report(struct usb_keyboard *keyboard, unsigned char *data, int size)
{
    struct input_dev *input = keyboard->input;
    unsigned char *keycode;
    int i;

    // Assuming the report format for a USB keyboard (HID boot protocol)
    // The first byte is the modifier byte (e.g., Shift, Ctrl)
    // The following bytes (from index 2 to 7) represent key codes (typically 6 bytes)

    if (size < 8) {
        printk(KERN_WARNING "Invalid report size\n");
        return -EINVAL;
    }

    keycode = &data[2]; // Starting from the 3rd byte (key codes)

    // Report key presses
    for (i = 0; i < 6; i++) {
        if (keycode[i]) {
            input_report_key(input, keycode[i], 1);  // Key down
        }
    }

    input_sync(input);

    // Report key releases
    for (i = 0; i < 6; i++) {
        if (keycode[i]) {
            input_report_key(input, keycode[i], 0);  // Key up
        }
    }

    input_sync(input);
    return 0;
}

static void keyboard_irq(struct urb *urb)
{
    struct usb_keyboard *keyboard = urb->context;
    unsigned char *data = urb->transfer_buffer;
    int size = urb->actual_length;

    if (urb->status) {
        printk(KERN_ERR "URB error: %d\n", urb->status);
        return;
    }

    // Parse the HID report
    parse_hid_report(keyboard, data, size);

    // Resubmit the URB to receive the next report
    usb_submit_urb(urb, GFP_ATOMIC);
}

static int keyboard_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
    struct usb_keyboard *keyboard;
    struct input_dev *input_dev;
    int retval;

    // Allocate memory for keyboard structure
    keyboard = kzalloc(sizeof(struct usb_keyboard), GFP_KERNEL);
    if (!keyboard)
        return -ENOMEM;

    keyboard->udev = usb_get_dev(interface_to_usbdev(interface));

    // Create input device
    input_dev = input_allocate_device();
    if (!input_dev) {
        kfree(keyboard);
        return -ENOMEM;
    }

    input_dev->name = "Custom USB Keyboard";
    input_dev->phys = "usb/keyboard";
    input_dev->id.bustype = BUS_USB;
    input_dev->evbit[0] = BIT(EV_KEY) | BIT(EV_SYN);
    input_dev->keybit[BIT_WORD(KEY_A)] = BIT(KEY_A) | BIT(KEY_B);  // Example keys

    // Register the input device
    retval = input_register_device(input_dev);
    if (retval) {
        input_free_device(input_dev);
        kfree(keyboard);
        return retval;
    }

    keyboard->input = input_dev;

    // Allocate memory for the URB and buffer
    keyboard->irq_buf = kmalloc(8, GFP_KERNEL);  // Buffer for a single HID report
    if (!keyboard->irq_buf) {
        input_unregister_device(input_dev);
        kfree(keyboard);
        return -ENOMEM;
    }

    keyboard->irq_urb = usb_alloc_urb(0, GFP_KERNEL);
    if (!keyboard->irq_urb) {
        kfree(keyboard->irq_buf);
        input_unregister_device(input_dev);
        kfree(keyboard);
        return -ENOMEM;
    }

    // Set up the URB to receive reports from the keyboard
    usb_fill_int_urb(keyboard->irq_urb, keyboard->udev,
                     usb_rcvintpipe(keyboard->udev, 0x81),  // Endpoint 0x81 for IN (Interrupt)
                     keyboard->irq_buf, 8,                  // 8 bytes for the HID report
                     keyboard_irq, keyboard, 10);          // 10ms polling interval

    // Submit the URB to start receiving HID reports
    retval = usb_submit_urb(keyboard->irq_urb, GFP_KERNEL);
    if (retval) {
        usb_free_urb(keyboard->irq_urb);
        kfree(keyboard->irq_buf);
        input_unregister_device(input_dev);
        kfree(keyboard);
        return retval;
    }

    usb_set_intfdata(interface, keyboard);

    return 0;
}

static void keyboard_disconnect(struct usb_interface *interface)
{
    struct usb_keyboard *keyboard = usb_get_intfdata(interface);

    // Cancel the URB and free the resources
    usb_kill_urb(keyboard->irq_urb);
    usb_free_urb(keyboard->irq_urb);
    kfree(keyboard->irq_buf);

    input_unregister_device(keyboard->input);
    usb_put_dev(keyboard->udev);
    kfree(keyboard);
}

static struct usb_driver keyboard_driver = {
    .name = "usb_keyboard_driver",
    .id_table = keyboard_table,
    .probe = keyboard_probe,
    .disconnect = keyboard_disconnect,
};

/*
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
		pr_err("input_allocate_device failedi\n");
		kfree(keyboard);
		return -ENOMEM;
	}

	input_device->name = "My keyboard";
	input_device->phys = "usbkbd/input0";
	input_device->id.bustype = BUS_USB;
	input_device->evbit[0] = BIT(EV_KEY) | BIT(EV_SYN);
	//Example, to change
	input_device->keybit[BIT_WORD(KEY_A)] = BIT(KEY_A) | BIT(KEY_B);

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
	usb_put_dev(keyboard->udev);
	kfree(keyboard);

	pr_debug("keyboard id disconnected\n");
}
*/

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

