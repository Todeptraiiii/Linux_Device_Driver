#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/kthread.h>
#include <linux/sched.h> // thread
#include <linux/delay.h>
#include <linux/err.h>

atomic_t etx_global_variable = ATOMIC_INIT(0);
unsigned int etx_bit_check = 0;


dev_t dev = 0;
static struct class *dev_class;
static struct cdev etx_cdev;
int completion_flag = 0;
 
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

int thread_function1(void *pv)
{
    unsigned int prev_value = 0;
    while(!kthread_should_stop())
    {
        atomic_inc(&etx_global_variable);
        prev_value = test_and_change_bit(1, (void*)&etx_bit_check);
        pr_info("Funtion1 [value : %u] [bit:%u]\n",atomic_read(&etx_global_variable),prev_value);
        msleep(1000);
    }
    return 0;
}
int thread_function2(void *pv)
{
    unsigned int prev_value = 0;
    while(!kthread_should_stop())
    {
        atomic_inc(&etx_global_variable);
        prev_value = test_and_change_bit(1, (void*)&etx_bit_check);
        pr_info("Funtion2 [value : %u] [bit:%u]\n",atomic_read(&etx_global_variable),prev_value);
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

        pr_info("Read function\n");
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

        etx_thread1 = kthread_run(thread_function1,NULL,"etx_thread1");
        if(etx_thread1)
        {
            pr_err("Kthread 1 tao thanh cong!! \n");
        }
        else
        {
            pr_err("Khong the tao kthread1\n");
            goto r_device;
        }

        etx_thread2 = kthread_run(thread_function2,NULL,"etx_thread1");
        if(etx_thread2)
        {
            pr_err("Kthread 2 tao thanh cong!! \n");
        }
        else
        {
            pr_err("Khong the tao kthread2\n");
            goto r_device;
        }

        printk(KERN_INFO "Device insert  DONE !!!!\n");
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

        kthread_stop(etx_thread1);
        kthread_stop(etx_thread2);
        device_destroy(dev_class,dev);
        class_destroy(dev_class);
        cdev_del(&etx_cdev);
        unregister_chrdev_region(dev, 1);
        printk(KERN_INFO "Device  2 Driver Remove...Done!!!\n");
}
 
module_init(etx_driver_init);
module_exit(etx_driver_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("To dep trai");
MODULE_DESCRIPTION("A simple device driver - Interrupts");
MODULE_VERSION("5.15");