#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/fs.h>
#include "query_ioctl.h"

#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/err.h>
#include <asm/uaccess.h>

#define FIRST_MINOR 0
#define MINOR_CNT 1

static dev_t dev;
static struct cdev c_dev;

static struct class *c1; // struct class dung de tao ra device file trong thu muc /sys/class
static int day = 11, month = 02, year = 1993;

static int my_open(struct inode *i, struct file *f);
static int my_close(struct inode *i, struct file *f);
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,35))
static int my_ioctl(struct inode *i, struct file *f, unsigned int cmnd, unsigned long arg);
#else
static long my_ioctl(struct file *f, unsigned int cmd, unsigned long arg);
#endif

static struct file_operations query_fops=
{
	.owner = THIS_MODULE,
	.open = my_open,
	.release = my_close,
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,5,35))
	.ioctl = my_ioctl
#else
	.unlocked_ioctl = my_ioctl
#endif
};

static void __init oni_init(void)
{
	int ret;
	struct device *dev_ret;

    if((ret = alloc_chrdev_region(&dev, FIRST_MINOR, MINOR_CNT,"query_ioctl"))<0)
    {
	    printk(KERN_WARNING "Cannot register device number range");
	    return ret;
    }

    // khoi tao character device voi cau truc cdev o tren va file_operation da dinh nghia
    // truoc do
    cdev_init(&c_dev, &query_fops);

    if((ret = cdev_add(&c_dev,dev,MINOR_CNT))<0)
    {
	    printk(KERN_WARNING "Cannot register device to kernel");
	    return ret;
    }
    // tao class cho device, sau buoc nay, device se xuat hien trong /sys/class directory
    if(IS_ERR(c1=class_create(THIS_MODULE,"char")))
    {
	    cdev_del(&c_dev);
	    unegister_chrdev_region(dev, MINOR_CNT);
	    printk(KERN_WARNING "Cannot create device class");
	    return PTR_ERR(c1);
    }

    // buoc cuoi cung cua init, tao device file
    if(IS_ERR(dev_ret = device_create(c1,NULL,dev,NULL,"query")))
    {
	    class_destroy(c1);
	    cdev_del(&c_dev);
	    unegister_chrdev_region(dev, MINOR_CNT);
	    printk(KERN_WARNING "Cannot create device file");
	    return PTR_ERR(dev_ret);
    }
    printk(KERN_NOTICE "LDD inserted successfully");
    return 0;
}

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,35))
static int my_ioctl(struct inode *i, struct file *f, unsigned int cmnd, unsigned long arg)
#else
static long my_ioctl(struct file *f, unsigned int cmd, unsigned long arg)
#endif
{
	birthday q;
	switch(cmd)
	{
		case QUERY_GET_VARIABLES:
			q.day = day;
			q.month = month;
			q.year = year;
			if(copy_to_user((query_arg_t *)arg, &q, sizeof(query_arg_t)))
			{
				return -EACCES;
			}
			break;
		case QUERY_CLR_VARIABLES:
			q.day = 1;
			q.month = 1;
			q.year = 1970;
		case QUERY_SET_VARIABLES:
			if(copy_from_user(&q,(query_arg_t *)arg,sizeof(query_arg_t)))
			{
				return -EACCES;
			}
			day = q.day;
			month = q.month;
			year = q.year;
			break;
		default:
			return -EINVAL
	}
	return 0;
}












