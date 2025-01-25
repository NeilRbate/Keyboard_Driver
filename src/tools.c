#include "../include/include.h"

const char *keycode_to_name[] = {
    "Reserved",                // 0x00
    "Error Roll-Over",         // 0x01
    "POST Error",              // 0x02
    "No Error",                // 0x03
    "A",                       // 0x04
    "B",                       // 0x05
    "C",                       // 0x06
    "D",                       // 0x07
    "E",                       // 0x08
    "F",                       // 0x09
    "G",                       // 0x0A
    "H",                       // 0x0B
    "I",                       // 0x0C
    "J",                       // 0x0D
    "K",                       // 0x0E
    "L",                       // 0x0F
    "M",                       // 0x10
    "N",                       // 0x11
    "O",                       // 0x12
    "P",                       // 0x13
    "Q",                       // 0x14
    "R",                       // 0x15
    "S",                       // 0x16
    "T",                       // 0x17
    "U",                       // 0x18
    "V",                       // 0x19
    "W",                       // 0x1A
    "X",                       // 0x1B
    "Y",                       // 0x1C
    "Z",                       // 0x1D
    "1",                       // 0x1E
    "2",                       // 0x1F
    "3",                       // 0x20
    "4",                       // 0x21
    "5",                       // 0x22
    "6",                       // 0x23
    "7",                       // 0x24
    "8",                       // 0x25
    "9",                       // 0x26
    "0",                       // 0x27
    "Enter",                   // 0x28
    "Esc",                     // 0x29
    "Backspace",               // 0x2A
    "Tab",                     // 0x2B
    "Space",                   // 0x2C
    "Minus",                   // 0x2D
    "Equals",                  // 0x2E
    "Left Bracket",            // 0x2F
    "Right Bracket",           // 0x30
    "Backslash",               // 0x31
    "Semicolon",               // 0x33
    "Quote",                   // 0x34
    "Grave",                   // 0x35
    "Comma",                   // 0x36
    "Period",                  // 0x37
    "Slash",                   // 0x38
    "Caps Lock",               // 0x39
    "F1",                      // 0x3A
    "F2",                      // 0x3B
    "F3",                      // 0x3C
    "F4",                      // 0x3D
    "F5",                      // 0x3E
    "F6",                      // 0x3F
    "F7",                      // 0x40
    "F8",                      // 0x41
    "F9",                      // 0x42
    "F10",                     // 0x43
    "F11",                     // 0x44
    "F12",                     // 0x45
    "Print Screen",            // 0x46
    "Scroll Lock",             // 0x47
    "Pause",                   // 0x48
    "Insert",                  // 0x49
    "Home",                    // 0x4A
    "Page Up",                 // 0x4B
    "Delete",                  // 0x4C
    "End",                     // 0x4D
    "Page Down",               // 0x4E
    "Right Arrow",             // 0x4F
    "Left Arrow",              // 0x50
    "Down Arrow",              // 0x51
    "Up Arrow",                // 0x52
    "Num Lock",                // 0x53
    "Keypad /",                // 0x54
    "Keypad *",                // 0x55
    "Keypad -",                // 0x56
    "Keypad +",                // 0x57
    "Keypad Enter",            // 0x58
    "Keypad 1",                // 0x59
    "Keypad 2",                // 0x5A
    "Keypad 3",                // 0x5B
    "Keypad 4",                // 0x5C
    "Keypad 5",                // 0x5D
    "Keypad 6",                // 0x5E
    "Keypad 7",                // 0x5F
    "Keypad 8",                // 0x60
    "Keypad 9",                // 0x61
    "Keypad 0",                // 0x62
    "Keypad .",                // 0x63
    "Non-US |",                // 0x64
    "Application",             // 0x65
    "Power",                   // 0x66
    "Keypad =",                // 0x67
    "F13",                     // 0x68
    "F14",                     // 0x69
    "F15",                     // 0x6A
    "F16",                     // 0x6B
    "F17",                     // 0x6C
    "F18",                     // 0x6D
    "F19",                     // 0x6E
    "F20",                     // 0x6F
    "F21",                     // 0x70
    "F22",                     // 0x71
    "F23",                     // 0x72
    "F24",                     // 0x73
    "Execute",                 // 0x74
    "Help",                    // 0x75
    "Menu",                    // 0x76
    "Select",                  // 0x77
    "Stop",                    // 0x78
    "Again",                   // 0x79
    "Undo",                    // 0x7A
    "Cut",                     // 0x7B
    "Copy",                    // 0x7C
    "Paste",                   // 0x7D
    "Find",                    // 0x7E
    "Mute",                    // 0x7F
    "Volume Up",               // 0x80
    "Volume Down",             // 0x81
    "Keypad Comma",            // 0x82
    "Keypad Equal Sign",       // 0x83
    "International 1",         // 0x84
    "International 2",         // 0x85
    "International 3",         // 0x86
    "International 4",         // 0x87
    "International 5",         // 0x88
    "International 6",         // 0x89
    "International 7",         // 0x8A
    "International 8",         // 0x8B
    "International 9",         // 0x8C
    "Lang 1",                  // 0x8D
    "Lang 2",                  // 0x8E
    "Lang 3",                  // 0x8F
    "Lang 4",                  // 0x90
    "Lang 5",                  // 0x91
    "Lang 6",                  // 0x92
    "Lang 7",                  // 0x93
    "Lang 8",                  // 0x94
    "Lang 9",                  // 0x95
    "Alt",                     // 0xE0
    "Control",                 // 0xE1
    "Shift",                   // 0xE2
    "Caps Lock",               // 0xE5
    "Left Arrow",              // 0xE6
    "Right Arrow",             // 0xE7
    "Up Arrow",                // 0xE8
    "Down Arrow",              // 0xE9
    "Scroll Lock",             // 0xEA
    "Num Lock",                // 0xEB
    "Insert",                  // 0xEC
    "Delete",                  // 0xED
    "Home",                    // 0xEE
    "End",                     // 0xEF
    "Page Up",                 // 0xF0
    "Page Down",               // 0xF1
};

/*
const char hid_to_linux_keycode[256] = {
    [0x00] = 0,
    [0x04] = KEY_A,
    [0x05] = KEY_B,
    [0x06] = KEY_C,
    [0x07] = KEY_D,
    [0x08] = KEY_E,
    [0x09] = KEY_F,
    [0x0A] = KEY_G,
    [0x0B] = KEY_H,
    [0x0C] = KEY_I,
    [0x0D] = KEY_J,
    [0x0E] = KEY_K,
    [0x0F] = KEY_L,
    [0x10] = KEY_M,
    [0x11] = KEY_N,
    [0x12] = KEY_O,
    [0x13] = KEY_P,
    [0x14] = KEY_Q,
    [0x15] = KEY_R,
    [0x16] = KEY_S,
    [0x17] = KEY_T,
    [0x18] = KEY_U,
    [0x19] = KEY_V,
    [0x1A] = KEY_W,
    [0x1B] = KEY_X,
    [0x1C] = KEY_Y,
    [0x1D] = KEY_Z,
    [0x1E] = KEY_1,
    [0x1F] = KEY_2,
    [0x20] = KEY_3,
    [0x21] = KEY_4,
    [0x22] = KEY_5,
    [0x23] = KEY_6,
    [0x24] = KEY_7,
    [0x25] = KEY_8,
    [0x26] = KEY_9,
    [0x27] = KEY_0,
    [0x28] = KEY_ENTER,
    [0x29] = KEY_ESC,
    [0x2A] = KEY_BACKSPACE,
    [0x2B] = KEY_TAB,
    [0x2C] = KEY_SPACE,
    [0x2D] = KEY_MINUS,
    [0x2E] = KEY_EQUAL,
    [0x2F] = KEY_LEFTBRACE,
    [0x30] = KEY_RIGHTBRACE,
    [0x31] = KEY_BACKSLASH,
    [0x32] = KEY_SEMICOLON,
    [0x33] = KEY_APOSTROPHE,
    [0x34] = KEY_GRAVE,
    [0x35] = KEY_COMMA,
    [0x36] = KEY_DOT,
    [0x37] = KEY_SLASH,
    [0x38] = KEY_CAPSLOCK,
    [0x39] = KEY_F1,
    [0x3A] = KEY_F2,
    [0x3B] = KEY_F3,
    [0x3C] = KEY_F4,
    [0x3D] = KEY_F5,
    [0x3E] = KEY_F6,
    [0x3F] = KEY_F7,
    [0x40] = KEY_F8,
    [0x41] = KEY_F9,
    [0x42] = KEY_F10,
    [0x43] = KEY_F11,
    [0x44] = KEY_F12
};
*/

const unsigned char hid_to_linux_keycode[256] = {
    [0x00] = 0,
    [0x01] = KEY_ESC,
    [0x02] = KEY_1,
    [0x03] = KEY_2,
    [0x04] = KEY_3,
    [0x05] = KEY_4,
    [0x06] = KEY_5,
    [0x07] = KEY_6,
    [0x08] = KEY_7,
    [0x09] = KEY_8,
    [0x0A] = KEY_9,
    [0x0B] = KEY_0,
    [0x0C] = KEY_MINUS,
    [0x0D] = KEY_EQUAL,
    [0x0E] = KEY_BACKSPACE,
    [0x0F] = KEY_TAB,
    [0x10] = KEY_Q,
    [0x11] = KEY_W,
    [0x12] = KEY_E,
    [0x13] = KEY_R,
    [0x14] = KEY_T,
    [0x15] = KEY_Y,
    [0x16] = KEY_U,
    [0x17] = KEY_I,
    [0x18] = KEY_O,
    [0x19] = KEY_P,
    [0x1A] = KEY_LEFTBRACE,
    [0x1B] = KEY_RIGHTBRACE,
    [0x1C] = KEY_ENTER,
    [0x1D] = KEY_LEFTCTRL,
    [0x1E] = KEY_A,
    [0x1F] = KEY_S,
    [0x20] = KEY_D,
    [0x21] = KEY_F,
    [0x22] = KEY_G,
    [0x23] = KEY_H,
    [0x24] = KEY_J,
    [0x25] = KEY_K,
    [0x26] = KEY_L,
    [0x27] = KEY_SEMICOLON,
    [0x28] = KEY_APOSTROPHE,
    [0x29] = KEY_GRAVE,
    [0x2A] = KEY_LEFTSHIFT,
    [0x2B] = KEY_BACKSLASH,
    [0x2C] = KEY_Z,
    [0x2D] = KEY_X,
    [0x2E] = KEY_C,
    [0x2F] = KEY_V,
    [0x30] = KEY_B,
    [0x31] = KEY_N,
    [0x32] = KEY_M,
    [0x33] = KEY_COMMA,
    [0x34] = KEY_DOT,
    [0x35] = KEY_SLASH,
    [0x36] = KEY_RIGHTSHIFT,
    [0x37] = KEY_KPASTERISK,
    [0x38] = KEY_LEFTALT,
    [0x39] = KEY_SPACE,
    [0x3A] = KEY_CAPSLOCK,
    [0x3B] = KEY_F1,
    [0x3C] = KEY_F2,
    [0x3D] = KEY_F3,
    [0x3E] = KEY_F4,
    [0x3F] = KEY_F5,
    [0x40] = KEY_F6,
    [0x41] = KEY_F7,
    [0x42] = KEY_F8,
    [0x43] = KEY_F9,
    [0x44] = KEY_F10,
    [0x45] = KEY_F11,
    [0x46] = KEY_F12,
    [0x47] = KEY_NUMLOCK,
    [0x48] = KEY_KP7,
    [0x49] = KEY_KP8,
    [0x4A] = KEY_KP9,
    [0x4B] = KEY_KPMINUS,
    [0x4C] = KEY_KP4,
    [0x4D] = KEY_KP5,
    [0x4E] = KEY_KP6,
    [0x4F] = KEY_KPPLUS,
    [0x50] = KEY_KP1,
    [0x51] = KEY_KP2,
    [0x52] = KEY_KP3,
    [0x53] = KEY_KP0,
    [0x54] = KEY_KPDOT,
    [0x55] = KEY_ZENKAKUHANKAKU,
    [0x56] = KEY_102ND,
    [0x57] = KEY_F13,
    [0x58] = KEY_F14,
    [0x59] = KEY_F15,
    [0x5A] = KEY_F16,
    [0x5B] = KEY_F17,
    [0x5C] = KEY_F18,
    [0x5D] = KEY_F19,
    [0x5E] = KEY_F20,
    [0x5F] = KEY_F21,
    [0x60] = KEY_F22,
    [0x61] = KEY_F23,
    [0x62] = KEY_F24,
    [0x63] = KEY_PLAYPAUSE,
    [0x64] = KEY_STOPCD,
    [0x65] = KEY_PREVIOUSSONG,
    [0x66] = KEY_NEXTSONG,
    [0x67] = KEY_EJECTCD,
    [0x68] = KEY_VOLUMEUP,
    [0x69] = KEY_VOLUMEDOWN,
    [0x6A] = KEY_MUTE,
    [0x6B] = KEY_WWW,
    [0x6C] = KEY_BACK,
    [0x6D] = KEY_FORWARD,
    [0x6E] = KEY_STOP,
    [0x6F] = KEY_REFRESH,
    [0x70] = KEY_SEARCH,
    [0x71] = KEY_BOOKMARKS,
    [0x72] = KEY_COMPUTER,
    [0x73] = KEY_EMAIL,
    [0x75] = KEY_BACKSPACE,
    [0x76] = KEY_TAB,
    [0x77] = KEY_ENTER,
    [0x78] = KEY_INSERT,
    [0x79] = KEY_HOME,
    [0x7A] = KEY_PAGEUP,
    [0x7B] = KEY_DELETE,
    [0x7C] = KEY_END,
    [0x7D] = KEY_PAGEDOWN,
    [0x7E] = KEY_RIGHT,
    [0x7F] = KEY_LEFT,
    [0x80] = KEY_DOWN,
    [0x81] = KEY_UP,
    [0x84] = KEY_LEFTMETA,
    [0x85] = KEY_RIGHTMETA,
    [0x87] = KEY_POWER,
    [0x88] = KEY_SLEEP,
    [0x89] = KEY_WAKEUP,
    [0x8A] = KEY_LIGHTS_TOGGLE,
};

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
		if (keycode[i])
			input_report_key(input, hid_to_linux_keycode[keycode[i]], 1);
	}
	input_sync(input);

	//Key up
	for (i = 0; i < 6; i++) {
		if (keycode[i])
			input_report_key(input, hid_to_linux_keycode[keycode[i]], 0);
	}
	input_sync(input);

	return 0;
}

EXPORT_SYMBOL_GPL(parse_hid_report);
