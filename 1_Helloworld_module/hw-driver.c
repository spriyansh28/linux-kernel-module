#include <linux/init.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
// Module metadata
MODULE_AUTHOR("Priyansh");
MODULE_DESCRIPTION("Hello world module");
MODULE_LICENSE("GPL");
static struct proc_dir_entry* proc_entry;
static ssize_t custom_read(struct file* file, char __user* user_buffer, size_t count, loff_t* offset)
{
 printk(KERN_INFO "reading from proc.");
 char greeting[] = "Hello world!\n";
 int greeting_length = strlen(greeting);
 if (*offset > 0)
  return 0;
 copy_to_user(user_buffer, greeting, greeting_length);
 *offset = greeting_length;
 return greeting_length;
}
static struct file_operations fops =
{
 .owner = THIS_MODULE,
 .read = custom_read
};
// Custom init and exit methods
static int __init custom_init(void) {
 proc_entry = proc_create("helloworldmodule", 0666, NULL, &fops);
 printk(KERN_INFO "Hello world module loaded.");
 return 0;
}
static void __exit custom_exit(void) {
 proc_remove(proc_entry);
 printk(KERN_INFO "Goodbye...");
}
module_init(custom_init);
module_exit(custom_exit);
