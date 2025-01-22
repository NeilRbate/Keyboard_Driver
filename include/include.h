#ifndef __KEYBOARD_DRIVER__
# define __KEYBOARD_DRIVER__

#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/usb.h>
#include <linux/input.h>

#define USB_KEYBOARD_VENDOR_ID 0x046d
#define USB_KEYBOARD_PRODUCT_ID 0xc328

static struct usb_device_id keyboard_table [] = {
        { USB_DEVICE(USB_KEYBOARD_VENDOR_ID, USB_KEYBOARD_PRODUCT_ID) },
        { }
};

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Julien Barbate");
MODULE_DESCRIPTION("This is an USB keyboard device driver");

#endif
