#include "../include/include.h"

bool	is_kp(unsigned char keycode);
unsigned char convert_kp(unsigned char keycode);

const int hid_to_linux_keycode[256] = {
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
	[0x2E] = KEY_EQUAL,
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

	//NUMPAD ROW 1
	[0x53] = KEY_NUMLOCK,
	[0x54] = KEY_KPSLASH,
	[0x55] = KEY_KPASTERISK,
	[0x56] = KEY_KPMINUS,

	//NUMPAD ROW 2
	[0x5F] = KEY_KP7,
	[0x60] = KEY_KP8,
	[0x61] = KEY_KP9,
	[0x57] = KEY_KPPLUS,
	
	//NUMPAD ROW 3
	[0x5C] = KEY_KP4,
	[0x5D] = KEY_KP5,
	[0x5E] = KEY_KP6,
	
	//NUMPAD ROW 4
	[0x59] = KEY_KP1,
	[0x5A] = KEY_KP2,
	[0x5B] = KEY_KP3,
	[0x58] = KEY_KPENTER,

	//NUMPAD ROW 5
	[0x62] = KEY_KP0,
	[0x63] = KEY_KPDOT,
};

static const struct {
	unsigned int mask;
	unsigned int keycode;
} modifiers_key[] = {
	{0x02, KEY_LEFTSHIFT},
	{0x20, KEY_RIGHTSHIFT},
	{0x01, KEY_LEFTCTRL},
	{0x10, KEY_RIGHTCTRL},
	{0x04, KEY_LEFTALT},
	{0x40, KEY_RIGHTALT},
};

bool	is_kp(unsigned char keycode)
{
	if (keycode >= 0x54 && keycode <= 0x63)
		return true;
	return false;
}

unsigned char convert_kp(unsigned char keycode)
{
	switch (keycode) {

	case 0x59:
		return KEY_END;
	case 0x5A:
		return KEY_DOWN;
	case 0x5B:
		return KEY_PAGEDOWN;
	case 0x5C:
		return KEY_LEFT;
	case 0x5E:
		return KEY_RIGHT;
	case 0x5F:
		return KEY_HOME;
	case 0x60:
		return KEY_UP;
	case 0x61:
		return KEY_PAGEUP;
	case 0x62:
		return KEY_INSERT;
	case 0x63:
		return KEY_DELETE;
	default:
		return 0;
	}
}

int parse_hid_report(struct usb_keyboard *keyboard, unsigned char *data, int size)
{

	int			i;
	struct input_dev	*input;
	unsigned char		*keycode;
	unsigned int		modifiers;
	static unsigned int	prev_modifiers = 0;
	static unsigned char	prev_keycode[6] = {0};
	static bool		capslock = false;
	static bool		numlock	= false;


	if (size < 8) {
		pr_err("invalid report size\n");
		return -EINVAL;
	}

	
	input = keyboard->input;
	keycode = &data[2];
	modifiers = data[0];

	//Search for pressed modifiers key (Shift, Ctrl, Alt)
	for (i = 0; i < 6; i++) {
		if ((modifiers & modifiers_key[i].mask) != (prev_modifiers & modifiers_key[i].mask)) {
			input_report_key(input, modifiers_key[i].keycode,
					(modifiers & modifiers_key[i].mask) ? 1 : 0);
		}
	}

	//Search for pressed key
	for (i = 0; i < 6; i++) {
		if (keycode[i] && !memchr(prev_keycode, keycode[i], 6)) {
			unsigned char key = hid_to_linux_keycode[keycode[i]];
			if (key == KEY_CAPSLOCK) {
				if (capslock == true) {
					input_report_key(input, KEY_LEFTSHIFT, 0);
					capslock = false;
				} else {
					capslock = true;
				}
			}

			if (key == KEY_NUMLOCK) {
				numlock = !numlock;
			}
			if (capslock)
				input_report_key(input, KEY_LEFTSHIFT, 1);

			if (!numlock && is_kp(keycode[i])) {
				key = convert_kp(keycode[i]);
				input_report_key(input, key, 1);
				input_report_key(input, key, 0);
				input_sync(input);
				return 0;
			}

			input_report_key(input, key, 1);
		}
	}

	//Search for unpressed key
	for (i = 0; i < 6; i++) {
		if (prev_keycode[i] && !memchr(keycode, prev_keycode[i], 6)) {
			unsigned char key = hid_to_linux_keycode[prev_keycode[i]];

			if (!numlock && is_kp(keycode[i]))
				key = convert_kp(keycode[i]);

			input_report_key(input, key, 0);
		}
	}

	input_sync(input);

	prev_modifiers = modifiers;
	memcpy(prev_keycode, keycode, 6);

	return 0;
}
EXPORT_SYMBOL_GPL(parse_hid_report);
