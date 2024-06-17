#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include<linux/slab.h>                 //kmalloc()
#include<linux/uaccess.h>              //copy_to/from_user()
#include<linux/sysfs.h> 
#include<linux/kobject.h> 
#include <linux/interrupt.h>
#include <asm/io.h>
#include <asm/hw_irq.h>
#include <linux/err.h>
#include <linux/list.h>

#define IRQ_NO 11
volatile int etx_value = 0;

dev_t dev = 0 ;
static struct class *dev_class;
static struct cdev etx_cdev;
struct kobject *kobj_ref;

static int __init etx_driver_init(void);
static void __exit etx_driver_exit(void);

static struct workqueue_struct *own_workqueue;

static void workqueue_fn(struct work_struct *work);

static DECLARE_WORK(work,workqueue_fn);

/* Khoi tao cac node*/
struct my_list
{
    int data;
    struct list_head list;
};

typedef struct my_list node;

/* Tao node head*/
LIST_HEAD(Head_Node); /* Thay rang thang nay khoi tao la gia tri */

/* Nguyen mau ham*/

static int etx_open(struct inode *inode, struct file *file);
static int etx_release(struct inode *inode, struct file *file);
static ssize_t etx_read(struct file *filp, char __user *buf, size_t len, loff_t *off);
static ssize_t etx_write(struct file *filp, const char __user *buf, size_t len, loff_t *off);

/* Workqueue Function*/
static void workqueue_fn(struct work_struct *work)
{
    node *temp_node = NULL;
    printk(KERN_INFO "Dang hoat dong trong workqueue function! \n");

    /* phan bo bo nho cho node*/
    temp_node = kmalloc(sizeof(node),GFP_KERNEL);
    /* Gan data nhan duoc vao node*/
    temp_node->data = etx_value;
    /* Khoi tao prev va next */
    INIT_LIST_HEAD(&temp_node-> list); // truyen dia chi cua gia tri, vi ham nay goi con tro
    /* Them node vao DSLK, them vao cuoi push back*/
    list_add_tail(&temp_node->list,&Head_Node);

} 
/* Interrupt handler cho IRQ 11*/
static irqreturn_t irq_handler(int irq, void *dev_it)
{
    printk(KERN_INFO "Shared IRQ: Interrupt Occurred \n");
    /* Them  work vao trong workqueue*/
    queue_work(own_workqueue, &work);

    return IRQ_HANDLED;
}
/* File operation structure*/

static struct file_operations fops = 
{
    .owner = THIS_MODULE,
    .read = etx_read,
    .write = etx_write,
    .open = etx_open,
    .release = etx_release,
};

/* Function duoc goi khi mo device file*/

static int etx_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "Device File Opened..\n");
    return 0;
}
/* Dong device file*/
static int etx_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "Device File Closed .. \n");
    return 0;
}
static ssize_t etx_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
    node *temp;
    int count = 0;
    printk(KERN_INFO "Read function \n");
    /* Duyet Linked List va In nhung node ra*/
    list_for_each_entry(temp,&Head_Node,list)
    {
        printk(KERN_INFO "Node %d data = %d \n",count++,temp->data);
    }
    pr_info("Tong so node : %d \n", count);
    return 0;
}
static ssize_t etx_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
    pr_info("Write Funtion \n");
    sscanf(buf,"%d",&etx_value);
    irq_handler(IRQ_NO,NULL); /* thay vi kernel goi irp thi minh tu goi*/
    return len;
}

static int __init etx_driver_init(void)
{
        /*Allocating Major number*/
        if((alloc_chrdev_region(&dev, 0, 1, "etx_Dev")) <0)
        {
                printk(KERN_INFO "Cannot allocate major number\n");
                return -1;
        }
        printk(KERN_INFO "Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));
 
        /*Creating cdev structure*/
        cdev_init(&etx_cdev,&fops);
 
        /*Adding character device to the system*/
        if((cdev_add(&etx_cdev,dev,1)) < 0)
        {
            printk(KERN_INFO "Cannot add the device to the system\n");
            goto r_class;
        }
 
        /*Creating struct class*/
        if(IS_ERR(dev_class = class_create(THIS_MODULE,"etx_class")))
        {
            printk(KERN_INFO "Cannot create the struct class\n");
            goto r_class;
        }
 
        /*Creating device*/
        if(IS_ERR(device_create(dev_class,NULL,dev,NULL,"etx_device")))
        {
            printk(KERN_INFO "Cannot create the Device 1\n");
            goto r_device;
        }
 
        /*Creating a directory in /sys/kernel/ */
        // kobj_ref = kobject_create_and_add("etx_sysfs",kernel_kobj);
 
        // /*Creating sysfs file for etx_value*/
        // if(sysfs_create_file(kobj_ref,&etx_attr.attr))
        // {
        //         printk(KERN_INFO"Cannot create sysfs file......\n");
        //         goto r_sysfs;
        // }

        if (request_irq(IRQ_NO, irq_handler, IRQF_SHARED, "etx_device", (void *)(irq_handler))) 
        {
            printk(KERN_INFO "my_device: cannot register IRQ ");
                    goto irq;
        }

        /* Khoi tao cong viec cho workqueue*/
        own_workqueue = create_workqueue("own_wq");
        printk(KERN_INFO "Device Driver Insert...Done!!!\n");
        return 0;
 
irq:
        free_irq(IRQ_NO,(void *)(irq_handler));
 
// r_sysfs:
//         kobject_put(kobj_ref); 
//         sysfs_remove_file(kernel_kobj, &etx_attr.attr);
 
r_device:
        class_destroy(dev_class);
r_class:
        unregister_chrdev_region(dev,1);
        cdev_del(&etx_cdev);
        return -1;
}
static void __exit etx_driver_exit(void)
{
        /*Duyet qua cac node va free memory*/
        node *cursor, *temp;
        list_for_each_entry_safe(temp,cursor,&Head_Node,list)
        {
            list_del(&cursor->list); // Xoa node khoi ds lien ket
            kfree(cursor); // free node vi list del khong hoan tra bo nho
        }
        /*Delete workqueue*/
        destroy_workqueue(own_workqueue);
        free_irq(IRQ_NO,(void *)(irq_handler));
        kobject_put(kobj_ref); 
        // sysfs_remove_file(kernel_kobj, &etx_attr.attr);
        device_destroy(dev_class,dev);
        class_destroy(dev_class);
        cdev_del(&etx_cdev);
        unregister_chrdev_region(dev, 1);
        printk(KERN_INFO "Device Driver Remove...Done!!!\n");
}

module_init(etx_driver_init);
module_exit(etx_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("EmbetronicX");