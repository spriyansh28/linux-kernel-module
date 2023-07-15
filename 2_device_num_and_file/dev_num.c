#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Priyansh");
MODULE_DESCRIPTION("Registers device num and implement callback");


//function called when device file is opened
static int open_driver(struct inode *device_file, struct file *instance) {
	printk("dev_num - open was called\n");
	return 0;
}

// function called when device file is closed
static int close_driver(struct inode *device_file, struct file *instance) {
	printk("dev_num - close was called\n");
	return 0;
}

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = open_driver,
	.release = close_driver
};

#define MYMAJOR 64


// init function 
static int __init ModuleInit(void) {
	int retval;
	printk("Hello world!\n");
	retval = register_chrdev(MYMAJOR, "my_dev_num", &fops);
	if(retval == 0) {
		printk("dev_num - registered Device number Major: %d, Minor: %d\n", MYMAJOR, 0);
	}
	else if(retval < 0) {
		printk("Could not register device number!\n");
		return -1;
	}
	return 0;
}


//Exit func that remove device num
static void __exit ModuleExit(void) {
	unregister_chrdev(MYMAJOR, "my_dev_num");
	printk("Goodbye...\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);


