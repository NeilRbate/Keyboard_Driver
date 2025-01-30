#include "../include/include.h"

static void write_log_to_file(const char *data)
{
	struct file	*file;
	loff_t		pos;

	pos = 0;

	file = filp_open("/tmp/keyboard_log", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (IS_ERR(file)) {
		pr_err("failed to open file /tmp/keyboard_log\n");
		return;
	}

	kernel_write(file, data, strlen(data), &pos);
	filp_close(file,NULL);
}

static unsigned int key_pressed_count[256];

static void increment_pressed_key(unsigned char keycode)
{
	if (keycode < 256)
		key_pressed_count[keycode]++;
}
void save_keyboard_log(void)
{
	char	*buff;
	int 	len, size;
	struct key_event *cursor, *temp;


	spin_lock(&event_list_lock);

	for(int i = 0; i < 256; i++)
		key_pressed_count[i] = 0;

	list_for_each_entry_safe(cursor, temp, &event_list, list) {
		if (cursor->pressed == 'P')
			increment_pressed_key(cursor->keycode);
	}

	spin_unlock(&event_list_lock);

	buff = kzalloc(4096, GFP_KERNEL);
	if (!buff) {
		pr_err("failed to allocate memory\n");
		return;
	}

	len = 0;
	size = 4096;

	len += snprintf(buff + len, size - len, "      --- Keyboard stat log ---\n" );
	len += snprintf(buff + len, size - len, 
			"ROW 1:   ESC[%d]  F1[%d]  F2[%d] F3[%d] F4[%d] F5[%d] F6[%d] F7[%d] F8[%d] F9[%d] F10[%d] F11[%d]   F12[%d] PRINT[%d] SCROLLL[%d] BREAK[%d]\n",
			key_pressed_count[KEY_ESC], key_pressed_count[KEY_F1], key_pressed_count[KEY_F2], key_pressed_count[KEY_F3],
		       	key_pressed_count[KEY_F4], key_pressed_count[KEY_F5], key_pressed_count[KEY_F6], key_pressed_count[KEY_F7],
			key_pressed_count[KEY_F8], key_pressed_count[KEY_F9], key_pressed_count[KEY_F10], key_pressed_count[KEY_F11],
			key_pressed_count[KEY_F12] ,key_pressed_count[KEY_PRINT], key_pressed_count[KEY_SCROLLLOCK], key_pressed_count[KEY_BREAK]);
	len += snprintf(buff + len, size - len,
			"ROW 2:     `[%d]   1[%d]   2[%d]  3[%d]  4[%d]  5[%d]  6[%d]  7[%d]  8[%d]  9[%d]   0[%d]   -[%d]     =[%d]  BSPC[%d]     INS[%d]  HOME[%d]   PUP[%d] NLOCK[%d] /[%d] *[%d] -[%d]\n",
			key_pressed_count[KEY_GRAVE], key_pressed_count[KEY_1], key_pressed_count[KEY_2],  key_pressed_count[KEY_3],
			key_pressed_count[KEY_4], key_pressed_count[KEY_5], key_pressed_count[KEY_6], key_pressed_count[KEY_7],
			key_pressed_count[KEY_8], key_pressed_count[KEY_9], key_pressed_count[KEY_0], key_pressed_count[KEY_MINUS], 
			key_pressed_count[KEY_EQUAL], key_pressed_count[KEY_BACKSPACE], key_pressed_count[KEY_INSERT], key_pressed_count[KEY_HOME],
			key_pressed_count[KEY_PAGEUP], key_pressed_count[KEY_NUMLOCK], key_pressed_count[KEY_KPSLASH], key_pressed_count[KEY_KPASTERISK],
			key_pressed_count[KEY_KPMINUS]);
	len += snprintf(buff + len, size - len,
			"ROW 3:   TAB[%d]   Q[%d]   W[%d]  E[%d]  R[%d]  T[%d]  Y[%d]  U[%d]  I[%d]  O[%d]   P[%d]   [[%d]     ][%d]   ENT[%d]     DEL[%d]   END[%d] PDOWN[%d]     7[%d] 8[%d] 9[%d] +[%d]\n",
			key_pressed_count[KEY_TAB], key_pressed_count[KEY_Q], key_pressed_count[KEY_W], key_pressed_count[KEY_E],
			key_pressed_count[KEY_R], key_pressed_count[KEY_T], key_pressed_count[KEY_Y], key_pressed_count[KEY_U],
			key_pressed_count[KEY_I], key_pressed_count[KEY_O], key_pressed_count[KEY_P], key_pressed_count[KEY_LEFTBRACE],
			key_pressed_count[KEY_RIGHTBRACE], key_pressed_count[KEY_ENTER], key_pressed_count[KEY_DELETE], key_pressed_count[KEY_END],
			key_pressed_count[KEY_PAGEDOWN], key_pressed_count[KEY_KP7], key_pressed_count[KEY_KP8], key_pressed_count[KEY_KP9], 
			key_pressed_count[KEY_KPPLUS]);

	len += snprintf(buff + len, size - len,
			"ROW 4: CAPSL[%d]   A[%d]   S[%d]  D[%d]  F[%d]  G[%d]  H[%d]  J[%d]  K[%d]  L[%d]   ;[%d]   '[%d]     \\[%d]     4[%d]       5[%d]    6[%d]\n",
			key_pressed_count[KEY_CAPSLOCK], key_pressed_count[KEY_A], key_pressed_count[KEY_S], 
			key_pressed_count[KEY_D], key_pressed_count[KEY_F], key_pressed_count[KEY_G], key_pressed_count[KEY_H], 
			key_pressed_count[KEY_J], key_pressed_count[KEY_K], key_pressed_count[KEY_L], 
			key_pressed_count[KEY_SEMICOLON], key_pressed_count[KEY_APOSTROPHE],
			key_pressed_count[KEY_BACKSLASH], key_pressed_count[KEY_KP4], key_pressed_count[KEY_KP5],
		        key_pressed_count[KEY_KP6]);
	len += snprintf(buff + len, size - len,
			"ROW 5: SHIFT[%d]   \\[%d]   Z[%d]  X[%d]  C[%d]  V[%d]  B[%d]  N[%d]  M[%d]  ,[%d]   .[%d]   /[%d] SHIFT[%d]    UP[%d]       1[%d]    2[%d]      3[%d]   ENT[%d]\n",
			key_pressed_count[KEY_LEFTSHIFT], key_pressed_count[KEY_BACKSLASH], key_pressed_count[KEY_Z],
			key_pressed_count[KEY_X], key_pressed_count[KEY_C], key_pressed_count[KEY_V], key_pressed_count[KEY_B],
			key_pressed_count[KEY_N], key_pressed_count[KEY_M], key_pressed_count[KEY_COMMA], key_pressed_count[KEY_DOT],
			key_pressed_count[KEY_SLASH], key_pressed_count[KEY_RIGHTSHIFT],key_pressed_count[KEY_UP],
			key_pressed_count[KEY_KP1], key_pressed_count[KEY_KP2], key_pressed_count[KEY_KP3], key_pressed_count[KEY_KPENTER]);

	len += snprintf(buff + len, size - len,
			"ROW 6:  CTRL[%d] WIN[%d] ALT[%d]    SPACE[%d]    ALTGR[%d] FN[%d]     CTRL[%d]       LEFT[%d]  DOWN[%d] RIGHT[%d]       0[%d]    .[%d]\n",
			key_pressed_count[KEY_LEFTCTRL], 0, key_pressed_count[KEY_LEFTALT], key_pressed_count[KEY_SPACE],
			key_pressed_count[KEY_RIGHTALT], 0, key_pressed_count[KEY_RIGHTCTRL], key_pressed_count[KEY_LEFT],
			key_pressed_count[KEY_DOWN], key_pressed_count[KEY_RIGHT], key_pressed_count[KEY_KP0], key_pressed_count[KEY_KPDOT]);

	write_log_to_file(buff);
	kfree(buff);
}
EXPORT_SYMBOL(save_keyboard_log);
