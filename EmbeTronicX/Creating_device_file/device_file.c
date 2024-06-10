#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/kdev_t.h>
#include <linux/err.h>

dev_t dev = 0;

static struct class *dev_class;

static int __init hello_world_init(void)
{
    // phan bo bo nho
    if((alloc_chrdev_region(&dev,0,1,"etx_Dev")) < 0)
    {
        pr_err("Khong the phan bo bo nho major va minor cho device\n");
        return -1;
    }
    pr_info("Major = %d, Minor = %d \n",MAJOR(dev),MINOR(dev));

    // tao class cho device
    dev_class = class_create(THIS_MODULE,"etx_class");
    if(IS_ERR(dev_class))
    {
        pr_err("Khong the tao class cho device \n");
        goto r_class;
    }

    // tao device file thuoc class vua tao
    if (IS_ERR(device_create(dev_class,NULL,dev,NULL,"etx_device")))
    {
        pr_err("Khong the tao device thuoc class tren \n");
        goto r_device;
    }

    pr_info("Kernel Module Inserted thanh cong .... \n");
    return 0;

r_class:
    // huy dang ky class
    class_destroy(dev_class);
r_device:
    // huy dang ky bo nho cho device
    unregister_chrdev_region(dev,1);
    return -1;

}

// Module exit function

static void __exit hello_world_exit(void)
{
    device_destroy(dev_class,dev);
    class_destroy(dev_class);
    unregister_chrdev_region(dev,1);
    pr_info("Kernel Module Removed thanh cong...!!\n");
}

module_init(hello_world_init);
module_exit(hello_world_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Todeptrai luyen tay");
MODULE_DESCRIPTION("Simple create device file");
MODULE_VERSION("5.15");

