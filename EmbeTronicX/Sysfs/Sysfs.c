/*--------------------------------------------------------------------
 file sysfs.c
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
#include <linux/proc_fs.h>

volatile int etx_value = 0;

dev_t dev = 0;
static struct class *dev_class;
static struct cdev etx_cdev;
struct kobject *kobj_ref;

// cac function duoc dung
static int __init etx_driver_init(void);
static void __exit etx_driver_exit(void);

/*************Driver Function *************************** */
static int etx_open(struct inode *inode, struct file *filp);
static int etx_release(struct inode *inode, struct file *filp);
static 	ssize_t etx_read(struct file * filp, char __user *buf, size_t len, loff_t * off);
static	ssize_t etx_write(struct file * filp, const char __user *buf, size_t len, loff_t * off);

/*************Sysfs Function *************************** */
static ssize_t sysfs_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t sysfs_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf,
                            size_t count);

struct kobj_attribute etx_attr = __ATTR(etx_value, 0660, sysfs_show, sysfs_store);

/**************File Operation *************************** */

static struct file_operations fops = 
{
    .owner = THIS_MODULE,
    .open = etx_open,
    .release = etx_release,
    .read = etx_read,
    .write = etx_write
};

/* Function nay se duoc goi khi chung ta doc sysfs file */
static ssize_t sysfs_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    pr_info("Sysfs - Read !!! \n");
    return sprintf(buf,"%d",etx_value); // dinh dang va luu tru mot chuoi vao buffer
}

static ssize_t sysfs_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf,
size_t count)
{
    pr_info("Sysfs - Write!!\n");
    sscanf(buf,"%d",&etx_value);
    return count;
}

/* Nhung function nay se duoc goi khi chung ta mo device file */

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

    /*Tao duong dan trong /sys/kernel */
    kobj_ref = kobject_create_and_add("etx_sysfs",kernel_kobj);

    // Tao sysfs file cho etx_value
    if(sysfs_create_file(kobj_ref,&etx_attr.attr))
    {
        pr_err("Khong the tao sysfs file ....\n");
        goto r_sysfs;
    }

    pr_info("Device Driver Insert ... Done !!! \n");
    return 0;

r_sysfs: 
    kobject_put(kobj_ref);
    sysfs_remove_file(kernel_kobj,&etx_attr.attr);
r_class:
    unregister_chrdev_region(dev,1);
    cdev_del(&etx_cdev);
r_device:
    class_destroy(dev_class);
    return -1;

}

static void __exit etx_driver_exit(void)
{

    // huy tao duong dan
    kobject_put(kobj_ref);
    // huy tao file sysfile
    sysfs_remove_file(kernel_kobj,&etx_attr.attr);
    // huy dang ky device thuoc class truoc da
    device_destroy(dev_class,dev);
    // huy dang ky class
    class_destroy(dev_class);
    // huy dang ky cac hanh dong da dang ky voi kernel de dieu khien hardware
    cdev_del(&etx_cdev);
    // Huy dang ky phan bo bo nho cho major number
    unregister_chrdev_region(dev,1);
    // Done
    pr_info("Device Driver Remove ..... DONE!!! \n");
    
}

module_init(etx_driver_init);
module_exit(etx_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("EmbetronicX");
MODULE_DESCRIPTION("Simple Driver Scull");
MODULE_VERSION("5.15");