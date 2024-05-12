#include <linux/init.h>
#include <linux/module.h>

static int __init hello_init(void)
{
    printk( "Hello, to dep trai!\n");
    return 0;
}

static void __exit hello_exit(void)
{
    printk( "Goodbye, to dep trai!\n");
}
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dao Van To");
MODULE_DESCRIPTION("A simple Linux kernel module");

module_init(hello_init);
module_exit(hello_exit);

