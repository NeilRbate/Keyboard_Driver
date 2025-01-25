#include "../include/include.h"

const char hid_to_linux_keycode[256] = {
	//Row 1
	[0x29] = KEY_ESC,
	[0x3A] = KEY_F1,
	[0x3B] = KEY_F2,
	[0x3C] = KEY_F3,
	[0x3D] = KEY_F4,
	[0x3E] = KEY_F5,
	[0x3F] = KEY_F6,
	[0x40] = KEY_F7,
	[0x41] = KEY_F8,
	[0x42] = KEY_F9,
	[0x43] = KEY_F10,
	[0X44] = KEY_F11,
	[0x45] = KEY_F12,
	[0x46] = KEY_PRINT,
	[0x47] = KEY_SCROLLLOCK,
	[0x48] = KEY_BREAK,

	//Row 2
	[0x35] = KEY_GRAVE,
	[0x1e] = KEY_1,
	[0x1f] = KEY_2,
	[0x20] = KEY_3,
	[0x21] = KEY_4,
	[0x22] = KEY_5,
	[0x23] = KEY_6,
	[0x24] = KEY_7,
	[0x25] = KEY_8,
	[0x26] = KEY_9,
	[0x27] = KEY_0,
	[0x2D] = KEY_MINUS,
	[0x2C] = KEY_EQUAL,
	[0x2A] = KEY_BACKSPACE,
	[0x49] = KEY_INSERT,
	[0x4A] = KEY_HOME,
	[0x4B] = KEY_PAGEUP,

	//Row 3
	[0x2B] = KEY_TAB,
	[0x14] = KEY_Q,
	[0x1A] = KEY_W,
	[0x08] = KEY_E,
	[0x15] = KEY_R,
	[0x17] = KEY_T,
	[0x1C] = KEY_Y,
	[0x18] = KEY_U,
	[0x0C] = KEY_I,
	[0x12] = KEY_O,
	[0x13] = KEY_P,
	[0x2F] = KEY_LEFTBRACE,
	[0x30] = KEY_RIGHTBRACE,
	[0x28] = KEY_ENTER,
	[0x4C] = KEY_DELETE,
	[0x4D] = KEY_END,
	[0x4E] = KEY_PAGEDOWN,
	
	//Row 4
	[0x39] = KEY_CAPSLOCK,
	[0x04] = KEY_A,
	[0x16] = KEY_S,
	[0x07] = KEY_D,
	[0x09] = KEY_F,
	[0x0A] = KEY_G,
	[0x0B] = KEY_H,
	[0x0D] = KEY_J,
	[0x0E] = KEY_K,
	[0x0F] = KEY_L,
	[0x33] = KEY_SEMICOLON,
	[0x34] = KEY_APOSTROPHE,
	[0x32] = KEY_BACKSLASH,

	//Row 5
	[0x64] = KEY_BACKSLASH,
	[0x1D] = KEY_Z,
	[0x1B] = KEY_X,
	[0x06] = KEY_C,
	[0x19] = KEY_V,
	[0x05] = KEY_B,
	[0x11] = KEY_N,
	[0x10] = KEY_M,
	[0x36] = KEY_COMMA,
	[0x37] = KEY_DOT,
	[0x38] = KEY_SLASH,

	//Row 6
	[0x2C] = KEY_SPACE,

	//Arrow
	[0x52] = KEY_UP,
	[0x50] = KEY_LEFT,
	[0x51] = KEY_DOWN,
	[0x4F] = KEY_RIGHT,
};

//TODO Catch shift + ctrl with modifier bit
static unsigned char	*compute_keycode(unsigned char *data)
{
	unsigned char	*keycode;

	keycode = &data[2];

	return keycode;
}

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
	keycode = &data[2];

	//Key down
	for (i = 0; i < 6; i++) {
		if (keycode[i]) {
			unsigned char correct_code = *compute_keycode(data);
			input_report_key(input, correct_code, 1);
		}
	}
	input_sync(input);

	//Key up
	for (i = 0; i < 6; i++) {
		if (keycode[i]) {
			unsigned char correct_code = *compute_keycode(data);
			input_report_key(input, correct_code, 0);
		}
	}
	input_sync(input);

	return 0;
}

EXPORT_SYMBOL_GPL(parse_hid_report);
