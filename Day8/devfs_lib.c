#include <linux/devfs_fs_kernel.h>

devfs_handle_t devfs_mk_dir(devfs_handle_t dir, const char *name, void *info);
devfs_handle_t devfs_register(devfs_handle_t dir, const char *name, unsigned int flags, unsigned int major, unsigned int minor, umode_t mode, void *ops, void *info);
void devfs_unregister(devfs_handle_t de);

int devfs_get_flags(devfs_handle_t de, unsigned int *flags);
int devfs_set_flags(devfs_handle_t de, unsigned int flags);
