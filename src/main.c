#include "../include/include.h"

static int __init keyboard_driver_init(void)
{
	int res;

	res = usb_register(&keyboard_driver);
	if (res) {
		pr_err("usb_register for %s failed. Error number %d\n",
				keyboard_driver.name, res);
		return res;
	}

	return 0;
}

static void __exit keyboard_driver_exit(void)
{
	usb_deregister(&keyboard_driver);
	pr_info("Exit module\n");
}

module_init(keyboard_driver_init);
module_exit(keyboard_driver_exit);

