#include "../include/include.h"

int parse_hid_report(struct usb_keyboard *keyboard, unsigned char *data, int size)
{
	struct input_dev *input;
	unsigned char *keycode;
	int i;

	if (size < 8) {
		pr_err("invalid report size\n");
		return -EINVAL;
	}

	input = keyboard->input;

	//Get the 3rd byte, the [0] and [1] are modifier byte
	keycode = &data[2];

	//Key down
	for (i = 0; i < 6; i++) {
		if (keycode[i] && keycode[i] < sizeof(keycode_to_name)/sizeof(keycode_to_name[0])) {
			printk(KERN_INFO "Key Pressed: %s\n", keycode_to_name[keycode[i]]);
			input_report_key(input, keycode[i], KEY_DOWN);
		}
	}
	input_sync(input);

	//Key up
	for (i = 0; i < 6; i++) {
		if (keycode[i]) {
			input_report_key(input, keycode[i], KEY_UP);
		}
	}
	input_sync(input);

	return 0;
}

EXPORT_SYMBOL_GPL(parse_hid_report);
