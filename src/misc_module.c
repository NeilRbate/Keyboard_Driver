#include "../include/include.h"

static const struct file_operations keyboard_file_ops = {
	.owner = THIS_MODULE,
	.read = keyboard_read,
};

struct miscdevice keyboard_misc_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "keyboard_module",
	.fops = &keyboard_file_ops,
};

ssize_t keyboard_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	char	*buff;
	struct	key_event *cursor, *temp;
	int	len, buff_size, ret;

	spin_lock(&event_list_lock);

	buff_size = 1024;
	len = 0;
	buff = kzalloc(buff_size, GFP_KERNEL);
	if (!buff) {
		spin_unlock(&event_list_lock);
		return -ENOMEM;
	}

	list_for_each_entry_safe(cursor, temp, &event_list, list) {

		while(len + 100 >= buff_size) {
			buff_size += 1024;
			char *t = krealloc(buff, buff_size, GFP_KERNEL);
			if (!t) {
				kfree(buff);
				spin_unlock(&event_list_lock);
				return -ENOMEM;
			}
			memset(t + (buff_size - 1024), 0, 1024);
			buff = t;
		}

		len += snprintf(buff + len, buff_size - len, "%lld:%lld:%lld Key [%s] Keycode [%d] Ascii Value [%d] State [%s]\n", 
				(long long)cursor->timestamp.tv_sec % 86400 / 3600,
				(long long)cursor->timestamp.tv_sec % 3600 / 60,
				(long long)cursor->timestamp.tv_sec % 60,
				cursor->key_name, cursor->keycode, cursor->ascii_value,
				cursor->pressed == 'P' ? "Pressed" : "Release");
	}

	spin_unlock(&event_list_lock);
	ret = simple_read_from_buffer(buf, count, f_pos, buff, len);

	kfree(buff);

	return ret;
}
EXPORT_SYMBOL(keyboard_read);

int keyboard_misc_register(void)
{
	int ret;

	ret = misc_register(&keyboard_misc_device);
	if (ret)
		pr_err("misc_register failed\n");
	return ret;
}
EXPORT_SYMBOL(keyboard_misc_register);

void keyboard_misc_deregister(void)
{
	misc_deregister(&keyboard_misc_device);
}
EXPORT_SYMBOL(keyboard_misc_deregister);
