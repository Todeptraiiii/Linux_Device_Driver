#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include<linux/slab.h>                 //kmalloc()
#include<linux/uaccess.h>              //copy_to/from_user()
#include<linux/kthread.h>               // kernel thread
#include <linux/sched.h>                // task_struct
#include <linux/delay.h>
#include <linux/mutex.h>                // mutex.h
#include <linux/err.h>

spinlock_t etx_spinlock;
unsigned long etx_global_variable = 0;

dev_t dev = 0;
static struct class *dev_class;
static struct cdev etx_cdev;
 
static int __init etx_driver_init(void);
static void __exit etx_driver_exit(void);

static struct task_struct *etx_thread1;
static struct task_struct *etx_thread2;
 
/*************** Driver Fuctions **********************/
static int etx_open(struct inode *inode, struct file *file);
static int etx_release(struct inode *inode, struct file *file);
static ssize_t etx_read(struct file *filp, 
                char __user *buf, size_t len,loff_t * off);
static ssize_t etx_write(struct file *filp, 
                const char *buf, size_t len, loff_t * off);

int thread_function1(void *pv);
int thread_function2(void *pv);

/*
    Thread function 1
*/

int thread_function1(void *pv) // dong thoi
{
    while(!kthread_should_stop())
    {
        if(!spin_is_locked(&etx_spinlock))
        {
            pr_info("Spinlock khong bi khoa boi Thread function 1");
        } 
        spin_lock(&etx_spinlock);
        if(spin_is_locked(&etx_spinlock))
        {
            pr_info("Spinlock da bi khoa boi Thread function 1");
        }
        etx_global_variable ++;
        pr_info("Dang trung function Thread 1 %lu \n", etx_global_variable);
        spin_unlock(&etx_spinlock);
        msleep(1000);
    }
        return 0;
}
/* Thread function 2*/
int thread_function2(void *pv) // dong thoi
{
    while(!kthread_should_stop())
    {
        spin_lock(&etx_spinlock);
        etx_global_variable++;
        pr_info("Dang trong thread function 2 %lu \n", etx_global_variable);
        spin_unlock(&etx_spinlock);
        msleep(1000);
    }
    return 0;
}

static struct file_operations fops =
{
    .owner = THIS_MODULE,
    .read = etx_read,
    .write = etx_write,
    .open = etx_open,
    .release = etx_release
};

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
        return 0; // so bai da doc
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
        spin_lock_init(&etx_spinlock);
        /* Tao Thread 1 */
        etx_thread1 = kthread_run(thread_function1,NULL,"etx thread1");
        if(etx_thread1)
        {
            pr_err("Kthread1 duoc tao thanh cong ... \n");
        } 
        else
        {
            pr_err("Khong the tao kthread1 \n");
            goto r_device;
        }

        /* Tao Thread 2 */
        etx_thread2 = kthread_run(thread_function2,NULL,"etx thread2");
        if(etx_thread2)
        {
            pr_err("Kthread2 duoc tao thanh cong ... \n");
        } 
        else
        {
            pr_err("Khong the tao kthread2 \n");
            goto r_device;
        }
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

        /*Kthread stop*/
        kthread_stop(etx_thread1);
        kthread_stop(etx_thread2);
        /*************/
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