#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/slab.h> // kmalloc()
#include <linux/uaccess.h> // copy_to/from_user()

#include <linux/kthread.h>
#include <linux/completion.h>
#include <linux/err.h>

uint32_t read_count = 0;
static struct task_struct *wait_thread;

struct completion data_read_done;

dev_t dev = 0;
static struct class *dev_class;
static struct cdev etx_cdev;
int completion_flag = 0;
 
static int __init etx_driver_init(void);
static void __exit etx_driver_exit(void);
 
/*************** Driver Fuctions **********************/
static int etx_open(struct inode *inode, struct file *file);
static int etx_release(struct inode *inode, struct file *file);
static ssize_t etx_read(struct file *filp, 
                char __user *buf, size_t len,loff_t * off);
static ssize_t etx_write(struct file *filp, 
                const char *buf, size_t len, loff_t * off);

static struct file_operations fops =
{
    .owner = THIS_MODULE,
    .read = etx_read,
    .write = etx_write,
    .open = etx_open,
    .release = etx_release
};

static int wait_function (void *unused)
{
    while(1)
    {
        pr_info("Waiting For Event...\n");
        wait_for_completion(&data_read_done);
        if(completion_flag == 2)
        {
            pr_info("Su kien den tu Exit Function \n");
            return 0;
        }
        pr_info("Su kien den tu Read Function - %d \n", ++ read_count);
        completion_flag = 0;
    }
    do_exit(0);
    return 0;
}

static int etx_open(struct inode *inode, struct file *file)
{
        printk(KERN_INFO "Device File Opened...!!!\n");
        return 0;
}
 
static int etx_release(struct inode *inode, struct file *file)
{
        printk(KERN_INFO "Device File Closed...!!!\n");
        return 0;
}
 
static ssize_t etx_read(struct file *filp, 
                char __user *buf, size_t len, loff_t *off)
{
        pr_info("Read function \n");
        completion_flag = 1;
        if(!completion_done(&data_read_done))
        {
            complete(&data_read_done);
        }
        return 0;
}

static ssize_t etx_write(struct file *filp, 
                const char __user *buf, size_t len, loff_t *off)
{
        printk(KERN_INFO "Write Function\n");
        return len;
}

static int __init etx_driver_init(void)
{
        /*Allocating Major number*/
        if((alloc_chrdev_region(&dev, 0, 1, "etx_Dev")) <0){
                printk(KERN_INFO "Cannot allocate major number\n");
                return -1;
        }
        printk(KERN_INFO "Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));
 
        /*Creating cdev structure*/
        cdev_init(&etx_cdev,&fops);
 
        /*Adding character device to the system*/
        if((cdev_add(&etx_cdev,dev,1)) < 0){
            printk(KERN_INFO "Cannot add the device to the system\n");
            goto r_class;
        }
 
        /*Creating struct class*/
        if(IS_ERR(dev_class = class_create(THIS_MODULE,"etx_class"))){
            printk(KERN_INFO "Cannot create the struct class\n");
            goto r_class;
        }
 
        /*Creating device*/
        if(IS_ERR(device_create(dev_class,NULL,dev,NULL,"etx_device"))){
            printk(KERN_INFO "Cannot create the Device 1\n");
            goto r_device;
        }

        // Tao ra kernel thread voi ten la 'my thread'
        wait_thread = kthread_create(wait_function, NULL, "WaitThread");
        if(wait_thread)
        {
            pr_info ("Thread tao thanh cong !! \n");
            wake_up_process(wait_thread);
        }
        else
        {
            pr_info("thread tao fail!\n");
        }
        // Khoi tao completion

        init_completion(&data_read_done);

        printk(KERN_INFO "Device insert DONE !!!!\n");
        return 0;
 
r_device:
        class_destroy(dev_class);
r_class:
        unregister_chrdev_region(dev,1);
        cdev_del(&etx_cdev);
        return -1;
}
 
static void __exit etx_driver_exit(void)
{

        completion_flag = 2;
        if(!completion_done(&data_read_done))
        {
            complete(&data_read_done);
        }

        device_destroy(dev_class,dev);
        class_destroy(dev_class);
        cdev_del(&etx_cdev);
        unregister_chrdev_region(dev, 1);
        printk(KERN_INFO "Device Driver Remove...Done!!!\n");
}
 
module_init(etx_driver_init);
module_exit(etx_driver_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("To dep trai");
MODULE_DESCRIPTION("A simple device driver - Interrupts");
MODULE_VERSION("5.15");