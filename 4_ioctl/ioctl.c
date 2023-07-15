#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/ioctl.h>
#include <linux/uaccess.h>

#include "ioctl_test.h"

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Priyansh");
MODULE_DESCRIPTION("A simple ioctl LKM");


/**
 * @brief This function is called, when the device file is opened
 */
static int driver_open(struct inode *device_file, struct file *instance) {
	printk("ioctl - open was called!\n");
	return 0;
}

/**
 * @brief This function is called, when the device file is opened
 */
static int driver_close(struct inode *device_file, struct file *instance) {
	printk("ioctl - close was called!\n");
	return 0;
}

/* Global Variable for reading and writing */
int32_t answer = 45452;

static long int my_ioctl(struct file *file, unsigned cmd, unsigned long arg){
	struct mystruct test;
	switch(cmd){
		case WR_VALUE:
			if(copy_from_user(&answer, (int32_t *) arg, sizeof(answer))) 
				printk("ioctl - Error copying data from user!\n");
			else
				printk("ioctl - Update the answer to %d\n", answer);
			break;
		case RD_VALUE:
			if(copy_to_user((int32_t *) arg, &answer, sizeof(answer))) 
				printk("ioctl - Error copying data to user!\n");
			else
				printk("ioctl - The answer was copied!\n");
			break;
	}
	return 0;
}

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = driver_open,
	.release = driver_close,
	.unlocked_ioctl = my_ioctl
};

#define MYMAJOR 64

/**
 * @brief This function is called, when the module is loaded into the kernel
 */
static int __init ModuleInit(void) {
	int retval;
	printk("Hello, Kernel!\n");
	/* register device nr. */
	retval = register_chrdev(MYMAJOR, "my_ioctl", &fops);
	if(retval == 0) {
		printk("ioctl - registered Device number Major: %d, Minor: %d\n", MYMAJOR, 0);
	}
	else if(retval > 0) {
		printk("ioctl - registered Device number Major: %d, Minor: %d\n", retval>>20, retval&0xfffff);
	}
	else {
		printk("Could not register device number!\n");
		return -1;
	}
	return 0;
}

/**
 * @brief This function is called, when the module is removed from the kernel
 */
static void __exit ModuleExit(void) {
	unregister_chrdev(MYMAJOR, "my_ioctl");
	printk("Goodbye, Kernel\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);


