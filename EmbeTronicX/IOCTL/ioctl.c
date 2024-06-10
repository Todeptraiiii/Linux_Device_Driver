/*--------------------------------------------------------------------
 file ioctl.c
 simple driver scull
 --------------------------------------------------------------------*/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/kdev_t.h>
#include <linux/err.h>
#include <linux/device.h>
#include <linux/slab.h> // copy to// from_user
#include <linux/uaccess.h> // kmalloc()
#include <linux/ioctl.h>

#define WR_VALUE _IOW('a','a', int32_t*)
#define RD_VALUE _IOR('a','b',int32_t*)

int32_t value = 0;

dev_t dev = 0;
static struct class *dev_class;
static struct cdev etx_cdev;

// cac function duoc dung
static int __init etx_driver_init(void);
static void __exit etx_driver_exit(void);
static int etx_open(struct inode *inode, struct file *filp);
static int etx_release(struct inode *inode, struct file *filp);
static 	ssize_t etx_read(struct file * filp, char __user *buf, size_t len, loff_t * off);
static	ssize_t etx_write(struct file * filp, const char __user *buf, size_t len, loff_t * off);
static long etx_ioctl(struct file *file, unsigned int cmd, unsigned long arg);

static struct file_operations fops = 
{
    .owner = THIS_MODULE,
    .open = etx_open,
    .release = etx_release,
    .read = etx_read,
    .write = etx_write,
    .unlocked_ioctl = etx_ioctl
};

// etx_open

static int etx_open(struct inode *inode, struct file *filp)
{
    pr_info("Device File Opened...!\n");
    return 0;
}
// etx_close
static int etx_release(struct inode *inode, struct file *filp)
{
    pr_info("Device File Closed...!!\n");
    return 0;
}

//etx_read
// Ham nay se duoc goi khi user doc du lieu tu device file
static 	ssize_t etx_read(struct file * filp, char __user *buf, size_t len, loff_t * off)
{
    pr_info("Read Function\n");
    return 0;
}
static	ssize_t etx_write(struct file * filp, const char __user *buf, size_t len, loff_t * off)
{

    pr_info("Write Function\n");
    return len;
}

static long etx_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    switch(cmd)
    {
        case WR_VALUE:
            if(copy_from_user(&value, (int32_t*) arg, sizeof(value)))
            {
                pr_err("Data Write : Err!\n");
            }
            pr_info("Value = %d\n",value);
            break;
        case RD_VALUE:
            if(copy_to_user((int32_t*)arg, &value,sizeof(value)))
            {
                pr_err("Data Read : Err! \n");
            }
            break;
        default:
            pr_info("Default\n");
            break;
    }
    return 0;
}

// module_init 
static int __init etx_driver_init(void)
{
    // phan bo bo nho cho major number
    if((alloc_chrdev_region(&dev,0,1,"etx_device")) < 0)
    {
        pr_info("Khong the phan bo bo nho cho major number");
    }
    pr_info("Major = %d Minor = %d \n", MAJOR(dev),MINOR(dev));

    // tao cdev struct, dang ki hanh dong voi kernel de tuong tac voi hardware 
    cdev_init(&etx_cdev,&fops);
    // Add character device vao he thong
    if(cdev_add(&etx_cdev,dev,1) < 0 ) // 1 la minor, co the lon hon 1 
    {
        pr_info("Khong the add device vao he thong \n");
        goto r_class;
    }
    // tao struct class
    if(IS_ERR(dev_class = class_create(THIS_MODULE,"etx_class")))
    {
        pr_info("Khong the tao struct class cho device \n");
        goto r_class;
    }
    // tao device 
    if(IS_ERR(device_create(dev_class,NULL,dev,NULL,"etx_device")))
    {
        pr_info ("Khong the tao device file \n");
        goto r_device;
    }

    pr_info("Device Driver Inserted.... DONE!!! \n");
    return 0;

r_class:
    unregister_chrdev_region(dev,1);
r_device:
    class_destroy(dev_class);
    return -1;

}

static void __exit etx_driver_exit(void)
{
    // Huy dang ky phan bo bo nho cho major number
    unregister_chrdev_region(dev,1);
    // huy dang ky device thuoc class truoc da
    device_destroy(dev_class,dev);
    // huy dang ky class
    class_destroy(dev_class);
    // huy dang ky cac hanh dong da dang ky voi kernel de dieu khien hardware
    cdev_del(&etx_cdev);
    // Done
    pr_info("Device Driver Remove ..... DONE!!! \n");
    
}

module_init(etx_driver_init);
module_exit(etx_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("EmbetronicX");
MODULE_DESCRIPTION("Simple Driver Scull");
MODULE_VERSION("5.15");