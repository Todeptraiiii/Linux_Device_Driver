#include <linux/module.h>
#include <linux/err.h>
#include <linux/cdev.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kdev_t.h>

dev_t dev = 0;
static struct class *dev_class;
static struct cdev etx_cdev;

// Goi function o day cho de xem co nhung function nao

static int __init etx_driver_init(void);
static void __exit etx_driver_exit(void);
static int etx_open(struct inode *inode, struct file *filp);
static int etx_release(struct inode *inode, struct file *filp); // filp : file pointer
static ssize_t etx_read(struct file *filp, char __user *buf, size_t len, loff_t *off);
static ssize_t etx_write(struct file *filp, const char *buf, size_t len,loff_t *off );


static struct file_operations fops =
{
    .owner = THIS_MODULE,
    .read = etx_read,
    .write = etx_write,
    .open = etx_open,
    .release = etx_release
};

// ham nay duoc goi khi mo device file
static int etx_open(struct inode *inode, struct file *file)
{
    pr_info("Driver Open Function Called ...!!!\n");
    return 0;
}

// ham nay duoc mo khi dong file
static int etx_release(struct inode *inode, struct file *filp)
{
    pr_info("Driver Release Function Called ...!!!\n");
    return 0;
}
// ham nay duoc goi khi doc file
static ssize_t etx_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
    pr_info("Driver read Function Called ...!!!\n");
    return 0;
}

// ham nay duoc goi khi ghi file
static ssize_t etx_write(struct file *filp, const char *buf, size_t len,loff_t *off )
{
    pr_info("Driver write Function Called ...!!!\n");
    return len;
}

static int __init etx_driver_init(void)
{
    // Phan bo bo nho cho Major number: Phan bo dong
    if((alloc_chrdev_region(&dev,0,1,"etx_Dev")) < 0)
    {
        pr_err("Cannot allocate major number \n");
        return -1;
    }
    pr_info ("Major = %d Minor = %d \n",MAJOR(dev),MINOR(dev));

    // Tao cau truc cdev: Hanh dong driver dang ki voi kernel
    cdev_init(&etx_cdev,&fops);

    // Add character device vao he thong

    if((cdev_add(&etx_cdev,dev,1)) < 0 )
    {
        pr_err("Cannot add the device to the system \n");
        goto r_class;
    }

    // tao struct class

    if(IS_ERR(dev_class = class_create(THIS_MODULE, "etx_module")))
    {
        pr_err("Khong the tao struct class \n");
        goto r_class;
    }

    // tao device thuoc class
    if(IS_ERR(device_create(dev_class,NULL,dev,NULL, "etx_device")))
    {
        pr_err ("Khog the tao device file");
        goto r_device;
    }
    pr_info("Device Driver Iserted .. DONE !!!!");
    return 0;

    r_class:
        unregister_chrdev_region(dev,1);
    r_device:
        class_destroy(dev_class);
        return -1;

}

static void __exit etx_driver_exit(void)
{

    // xoa cac hanh dong dong ma driver bao voi kernel tuong tac voi hardware
    cdev_del(&etx_cdev);
    // huy viec tao device file
    device_destroy(dev_class,dev);
    // huy viec tao class
    class_destroy(dev_class);
    // huy viec dang ky major number
    unregister_chrdev_region(dev,1);

    pr_info ("Loai bo kernel module thanh cong!!!!");
}


module_init(etx_driver_init);
module_exit(etx_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("To dep trai");
MODULE_DESCRIPTION("Simple dummy driver!!");
MODULE_VERSION("5.15");