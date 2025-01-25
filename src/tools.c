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
		if (keycode[i]) { 
			pr_debug("Keycode -> %x\n", keycode[i]);
			if (keycode[i] == 0x14)
				input_report_key(input, KEY_Q, KEY_DOWN);
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
