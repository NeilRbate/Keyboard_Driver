#include "../include/include.h"

static DEFINE_SPINLOCK(event_list_lock);

static struct key_translation keymap[] = {
    { KEY_A, "a", 'a' },
    { KEY_B, "b", 'b' },
    { KEY_C, "c", 'c' },
    { KEY_D, "d", 'd' },
    { KEY_E, "e", 'e' },
    { KEY_F, "f", 'f' },
    { KEY_G, "g", 'g' },
    { KEY_H, "h", 'h' },
    { KEY_I, "i", 'i' },
    { KEY_J, "j", 'j' },
    { KEY_K, "k", 'k' },
    { KEY_L, "l", 'l' },
    { KEY_M, "m", 'm' },
    { KEY_N, "n", 'n' },
    { KEY_O, "o", 'o' },
    { KEY_P, "p", 'p' },
    { KEY_Q, "q", 'q' },
    { KEY_R, "r", 'r' },
    { KEY_S, "s", 's' },
    { KEY_T, "t", 't' },
    { KEY_U, "u", 'u' },
    { KEY_V, "v", 'v' },
    { KEY_W, "w", 'w' },
    { KEY_X, "x", 'x' },
    { KEY_Y, "y", 'y' },
    { KEY_Z, "z", 'z' },

    { KEY_1, "1", '1' },
    { KEY_2, "2", '2' },
    { KEY_3, "3", '3' },
    { KEY_4, "4", '4' },
    { KEY_5, "5", '5' },
    { KEY_6, "6", '6' },
    { KEY_7, "7", '7' },
    { KEY_8, "8", '8' },
    { KEY_9, "9", '9' },
    { KEY_0, "0", '0' },

    { KEY_ENTER, "return", '\n' },
    { KEY_SPACE, "space", ' ' },
    { KEY_BACKSPACE, "backspace", '\b' },
    { KEY_TAB, "tab", '\t' },
    { KEY_ESC, "escape", 27 },

    { KEY_MINUS, "-", '-' },
    { KEY_EQUAL, "=", '=' },
    { KEY_LEFTBRACE, "[", '[' },
    { KEY_RIGHTBRACE, "]", ']' },
    { KEY_BACKSLASH, "\\", '\\' },
    { KEY_SEMICOLON, ";", ';' },
    { KEY_APOSTROPHE, "'", '\'' },
    { KEY_GRAVE, "`", '`' },
    { KEY_COMMA, ",", ',' },
    { KEY_DOT, ".", '.' },
    { KEY_SLASH, "/", '/' },

    { KEY_CAPSLOCK, "capslock", 0 },
    { KEY_NUMLOCK, "numlock", 0 },
    { KEY_LEFTSHIFT, "left shift", 0 },
    { KEY_RIGHTSHIFT, "right shift", 0 },
    { KEY_LEFTCTRL, "left ctrl", 0 },
    { KEY_RIGHTCTRL, "right ctrl", 0 },
    { KEY_LEFTALT, "left alt", 0 },
    { KEY_RIGHTALT, "right alt", 0 },

    { KEY_F1, "F1", 0 },
    { KEY_F2, "F2", 0 },
    { KEY_F3, "F3", 0 },
    { KEY_F4, "F4", 0 },
    { KEY_F5, "F5", 0 },
    { KEY_F6, "F6", 0 },
    { KEY_F7, "F7", 0 },
    { KEY_F8, "F8", 0 },
    { KEY_F9, "F9", 0 },
    { KEY_F10, "F10", 0 },
    { KEY_F11, "F11", 0 },
    { KEY_F12, "F12", 0 },

    { KEY_DELETE, "delete", 127 },
    { KEY_HOME, "home", 0 },
    { KEY_END, "end", 0 },
    { KEY_PAGEUP, "page up", 0 },
    { KEY_PAGEDOWN, "page down", 0 },
    { KEY_INSERT, "insert", 0 },
    { KEY_PRINT, "print", 0 },
    { KEY_SCROLLLOCK, "scroll lock", 0 },
    { KEY_BREAK, "break", 0 },

    { KEY_UP, "up", 0 },
    { KEY_DOWN, "down", 0 },
    { KEY_LEFT, "left", 0 },
    { KEY_RIGHT, "right", '0' },

    { KEY_KPSLASH, "/", '/' },
    { KEY_KPASTERISK, "*", '*' },
    { KEY_KPMINUS, "-", '-' },
    { KEY_KP7, "7", '7' },
    { KEY_KP8, "8", '8' },
    { KEY_KP9, "9", '9' },
    { KEY_KPPLUS, "+", '+' },
    { KEY_KP4, "4", '4' },
    { KEY_KP5, "5", '5' },
    { KEY_KP6, "6", '6' },
    { KEY_KP1, "1", '1' },
    { KEY_KP2, "2", '2' },
    { KEY_KP3, "3", '3' },
    { KEY_KPENTER, "return", '\n' },
    { KEY_KP0, "0", '0' },
    { KEY_KPDOT, ".", '.' },
};

static const struct key_translation *get_key_info(unsigned int keycode)
{
	for(int i = 0; keymap[i]. name != NULL; i++) {
		if (keymap[i].keycode == keycode)
			return &keymap[i];
	}
	return NULL;
}

void	add_key_event(unsigned char keycode, bool pressed)
{
	struct key_event	*event;
	struct timespec64	ts;

	const struct key_translation *data = get_key_info(keycode);

	if (data == NULL)
		return;

	event = kzalloc(sizeof(*event), GFP_KERNEL);
	if (!event) {
		pr_err("failed to allocated memory\n");
		return;
	}

	event->keycode = keycode;
	event->pressed = pressed ? 'P' : 'R';
	memset(event->key_name, 0, 32);
	memcpy(event->key_name, data->name, strlen(data->name));
	event->ascii_value = data->ascii;
	ktime_get_real_ts64(&ts);
	event->timestamp = ts;

	spin_lock(&event_list_lock);

	list_add_tail(&event->list, &event_list);

	spin_unlock(&event_list_lock);
}
EXPORT_SYMBOL(add_key_event);

void free_key_event_list(void)
{
	struct key_event *cursor, *temp;

	spin_lock(&event_list_lock);

	list_for_each_entry_safe(cursor, temp, &event_list, list) {
		list_del(&cursor->list);
		kfree(cursor);
	}


	spin_unlock(&event_list_lock);

}
EXPORT_SYMBOL(free_key_event_list);

void print_key_event_list(void) 
{
	struct key_event *cursor, *temp;

	spin_lock(&event_list_lock);

	list_for_each_entry_safe(cursor, temp, &event_list, list) {
		pr_info("%lld:%lld:%lld key[%s] keycode[(%d)] ascii_value[%d] state[%s]\n", 
				(long long)cursor->timestamp.tv_sec % 86400 / 3600,
				(long long)cursor->timestamp.tv_sec % 3600 / 60,
				(long long)cursor->timestamp.tv_sec % 60,
				cursor->key_name, cursor->keycode, cursor->ascii_value,
				cursor->pressed == 'P' ? "Pressed" : "Release");
	}

	spin_unlock(&event_list_lock);
}
EXPORT_SYMBOL(print_key_event_list);
