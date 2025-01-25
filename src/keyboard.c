#include "../include/include.h"

void keyboard_irq(struct urb *urb)
{
	struct usb_keyboard *keyboard;
	unsigned char *data;
	int size;

	keyboard = urb->context;
	data = urb->transfer_buffer;
       	size = urb->actual_length;

	if (urb->status) {
		pr_err("URB error: %d\n", urb->status);
		return;
	}

	parse_hid_report(keyboard, data, size);
	usb_submit_urb(urb, GFP_ATOMIC);
}

int keyboard_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
	struct usb_keyboard *keyboard;
	struct input_dev *input_dev;
	int res;

	keyboard = kzalloc(sizeof(struct usb_keyboard), GFP_KERNEL);
	if (!keyboard) {
		pr_err("failed to allocated memory\n");
		return -ENOMEM;
	}
	keyboard->udev = usb_get_dev(interface_to_usbdev(interface));

	input_dev = input_allocate_device();
	if (!input_dev) {
		pr_err("failed to allocated memory\n");
		kfree(keyboard);
		return -ENOMEM;
	}

	input_dev->name = "Custom USB Keyboard";
	input_dev->phys = "usb/keyboard";
	input_dev->id.bustype = BUS_USB;
	input_dev->evbit[0] = BIT(EV_KEY) | BIT(EV_SYN);
	input_dev->keybit[BIT_WORD(KEY_A)] = BIT(KEY_A) | BIT(KEY_B);  // Example keys

	res = input_register_device(input_dev);
	if (res) {
		pr_err("input_register_device failed. error number %d\n", res);
		input_free_device(input_dev);
		kfree(keyboard);
		return res;
	}

	keyboard->input = input_dev;

	keyboard->irq_buf = kmalloc(8, GFP_KERNEL);
	if (!keyboard->irq_buf) {
		pr_err("failed to allocated memory\n");
		input_unregister_device(input_dev);
		kfree(keyboard);
		return -ENOMEM;
	}

	keyboard->irq_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!keyboard->irq_urb) {
		pr_err("usb_alloc_urb failed\n");
		kfree(keyboard->irq_buf);
		input_unregister_device(input_dev);
		kfree(keyboard);
		return -ENOMEM;
	}

	usb_fill_int_urb(keyboard->irq_urb, keyboard->udev,
			usb_rcvintpipe(keyboard->udev, 0x81),  // Endpoint 0x81 for IN (Interrupt)
			keyboard->irq_buf, 8,                  // 8 bytes for the HID report
			keyboard_irq, keyboard, 10);          // 10ms polling interval

	res = usb_submit_urb(keyboard->irq_urb, GFP_KERNEL);
	if (res) {
		pr_err("usb_submit_urb failed\n");
		usb_free_urb(keyboard->irq_urb);
		kfree(keyboard->irq_buf);
		input_unregister_device(input_dev);
		kfree(keyboard);
		return res;
	}

	usb_set_intfdata(interface, keyboard);
	return 0;
}

void keyboard_disconnect(struct usb_interface *interface)
{
	struct usb_keyboard *keyboard = usb_get_intfdata(interface);

	usb_kill_urb(keyboard->irq_urb);
	usb_free_urb(keyboard->irq_urb);
	kfree(keyboard->irq_buf);

	input_unregister_device(keyboard->input);
	usb_put_dev(keyboard->udev);
	kfree(keyboard);
}

EXPORT_SYMBOL_GPL(keyboard_disconnect);
EXPORT_SYMBOL_GPL(keyboard_probe);
