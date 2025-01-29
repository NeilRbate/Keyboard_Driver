#ifndef __KEYBOARD_DRIVER__
# define __KEYBOARD_DRIVER__

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/usb.h>
#include <linux/input.h>
#include <linux/hid.h>

#define USB_KEYBOARD_VENDOR_ID 0x046d
#define USB_KEYBOARD_PRODUCT_ID 0xc328

extern struct usb_driver keyboard_driver;
extern struct usb_device_id keyboard_table[];

struct usb_keyboard {
    struct usb_device *udev;
    struct input_dev *input;
    struct urb *irq_urb;
    unsigned char *irq_buf;
};

struct key_event {
	unsigned int		keycode;
	char			pressed;
	char			key_name[32];
	char			ascii_value;
	struct timespec64	timestamp;
	struct list_head	list;
};

static LIST_HEAD(event_list);
static DEFINE_SPINLOCK(event_list_lock);

void keyboard_irq(struct urb *urb);
int keyboard_probe(struct usb_interface *interface, const struct usb_device_id *id);
void keyboard_disconnect(struct usb_interface *interface);
int parse_hid_report(struct usb_keyboard *keyboard, unsigned char *data, int size);

#endif
