#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/module.h>

int cbvalue = 0;

static int get_info(const char *val, const struct kernel_param *kp)
{
    int res;
    res = param_set_int(val,kp);
    if(res == 0)
    {
        printk(KERN_INFO "Bien da thay doi thanh: %d \n",cbvalue);
        return 0;
    }

    return -1;
}

struct kernel_param_ops my_param_ops =
{
    .set = &get_info,
    .get = &param_get_int
};

module_param_cb(cbvalue,&my_param_ops,&cbvalue,S_IRUSR | S_IWUSR);

static int __init hello_world_myself_init(void)
{
    printk(KERN_INFO "Hello_World DIY \n");
    return 0;
};

static void __exit hello_world_myself_exit(void)
{
    printk(KERN_INFO "GOod Bye. See you later \n");
};

module_init(hello_world_myself_init);
module_exit(hello_world_myself_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dao Van To");
MODULE_DESCRIPTION("Tu viet module param");
MODULE_VERSION("5.15");





