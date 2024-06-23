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
#include <linux/interrupt.h>
#include <linux/err.h>
#include <linux/signal.h>

#define SIGETX 44
#define REG_CURRENT_TASK _IOW('a','a',int32_t*)
#define IRQ_NO 11

/* Signal to app*/
static struct task_struct *task = NULL;
static int signum = 0 ;

int32_t value = 0;

dev_t dev = 0;
static struct class *dev_class;
static struct cdev etx_cdev;
 
static int __init etx_driver_init(void);
static void __exit etx_driver_exit(void);
 
/*************** Driver Fuctions **********************/
static int etx_open(struct inode *inode, struct file *file);
static int etx_release(struct inode *inode, struct file *file);
static ssize_t etx_read(struct file *filp, 
                char __user *buf, size_t len,loff_t * off);
static ssize_t etx_write(struct file *filp, 
                const char *buf, size_t len, loff_t * off);
static long etx_ioctl(struct file *file, unsigned int cmd, unsigned long arg);

static struct file_operations fops =
{
    .owner = THIS_MODULE,
    .read = etx_read,
    .write = etx_write,
    .open = etx_open,
    .release = etx_release,
    .unlocked_ioctl = etx_ioctl
};

// Interrupt handler for IRQ 11
static irqreturn_t irq_handler(int irq, void *dev_id)
{
    struct kernel_siginfo info;
    // sending signal to app
    memset(&info,0,sizeof(struct kernel_siginfo));
    info.si_signo = SIGETX;
    info.si_code = SI_QUEUE;
    info.si_int = 1;
    if(task != NULL)
    {
        printk("Sending signal to app \n");
        if(send_sig_info(SIGETX,&info,task) < 0 )
        {
            printk(KERN_INFO "Khong the gui signal \n");
        }
    }

    return IRQ_HANDLED;

}
//

static int etx_open(struct inode *inode, struct file *file)
{
        printk(KERN_INFO "Device File Opened...!!!\n");
        return 0;
}
 
static int etx_release(struct inode *inode, struct file *file)
{
        struct task_struct *ref_task = get_current();
        printk(KERN_INFO "Device File Closed...!!!\n");

        // delete the task
        if(ref_task == task)
        {
            task = NULL;
        }
        return 0;
}
 
static ssize_t etx_read(struct file *filp, 
                char __user *buf, size_t len, loff_t *off)
{
        pr_info("Read function \n");
        irq_handler(IRQ_NO,NULL);
        return 0; // so bai da doc
}

static ssize_t etx_write(struct file *filp, 
                const char __user *buf, size_t len, loff_t *off)
{
        printk(KERN_INFO "Write Function\n");
        return len;
}

static long etx_ioctl (struct file *file, unsigned int cmd, unsigned long arg)
{
    if(cmd == REG_CURRENT_TASK)
    {
        printk(KERN_INFO "REG_CURRENT_TASK \n");
        task = get_current();
        signum = SIGETX;
    }
    return 0;
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
        
        
        if(request_irq(IRQ_NO, irq_handler, IRQF_SHARED, "etx_device", (void *) (irq_handler)))
        {
            printk(KERN_INFO "my_device: cannot register IRQ");
            goto irq;
        }

        printk(KERN_INFO "Device insert DONE !!!!\n");
        return 0;
 
irq:
    free_irq(IRQ_NO, (void *) (irq_handler));
r_device:
        class_destroy(dev_class);
r_class:
        unregister_chrdev_region(dev,1);
        cdev_del(&etx_cdev);
        return -1;
}
 
static void __exit etx_driver_exit(void)
{

        free_irq(IRQ_NO, (void *) (irq_handler));
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