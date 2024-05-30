#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>


static int __init hello_init(void)
{
    printk( KERN_INFO "This is an informational message. \n");
    return 0;
}

static void __exit hello_exit(void)
{
    printk( "This is an error massage. \n");
}
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dao Van To");
MODULE_DESCRIPTION("A simple Linux kernel module");

module_init(hello_init);
module_exit(hello_exit);

