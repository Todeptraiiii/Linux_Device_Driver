#include <linux/errno.h>
#include <linux/module.h>
#include <linux/init.h>

struct something *item1;
struct somethingelse *item2;
int stuff_ok;

void cleanup_module(void)
{
    if (item1)
        release_thing(item1);
    if (item2)
        release_thing2(item2);
    if (stuff_ok)
        unregister_stuff();
    return;
}

int init_module(void)
{
    int err = -ENOMEM;
    item1 = allocate_thing(arguments);
    item2 = allocate_thing2(arguments2);
    if (!item2 || !item2)
        goto fail;
    err = register_stuff(item1, item2);
    if (!err)
        stuff_ok = 1;
    else
        goto fail;
    return 0; /* success */
fail:
    cleanup_module();
    return err;
}

