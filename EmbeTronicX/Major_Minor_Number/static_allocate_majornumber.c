#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

// tao dev de luu tru major number va minor number
dev_t dev = MKDEV(235,0);

static int __init hello_world_init(void)
{
    // dang ki bo nho tinh cho major number
    register_chrdev_region(dev,1,"first_dev");
    printk(KERN_INFO"Major = %d Minor = %d\n",MAJOR(dev),MINOR(dev));
    printk(KERN_INFO"Kernel Module Inserted Successfully....\n");
    return 0;
}

static void __exit hello_world_exit(void)
{
    unregister_chrdev_region(dev,1);
    printk(KERN_INFO"Kernel Module removed Successfully..\n");
}

module_init(hello_world_init);
module_exit(hello_world_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("EmbetronicX");
MODULE_DESCRIPTION("Simple declare major number static");
MODULE_VERSION("5.15");