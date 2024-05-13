#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>

static int __init my_current_process(void)
{
	printk("The process is \"%s\" (pid %i)\n)", current -> comm, current -> pid);
	return 0;
}

static void __exit end_current_process(void)
{
	printk ("The process end is:%s pid:%i \n ", current -> comm, current -> pid);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dao Van To");
MODULE_DESCRIPTION("A simple Linux kernel module of current process");

module_init(my_current_process);
module_exit(end_current_process);
