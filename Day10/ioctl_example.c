#include <linux/ioctl.h>

#define MY_IOCTL_MAGIC 'k'
#define MY_IOCTL_RESET _IO(MY_IOCTL_MAGIC, 0)
#define MY_IOCTL_SET_BAUD _IOW(MY_IOCTL_MAGIC, 1, int)
#define MY_IOCTL_GET_BAUD _IOR(MY_IOCTL_MAGIC, 2, int)

static long my_device_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    switch(cmd) {
        case MY_IOCTL_RESET:
            // Reset thiết bị
            break;
        case MY_IOCTL_SET_BAUD:
            // Thiết lập tốc độ baud
            int baud_rate;
            if (copy_from_user(&baud_rate, (int __user *)arg, sizeof(int))) {
                return -EFAULT;
            }
            // thiết lập tốc độ baud cho thiết bị
            break;
        case MY_IOCTL_GET_BAUD:
            // Lấy tốc độ baud hiện tại
            int current_baud_rate;
            // lấy tốc độ baud hiện tại từ thiết bị
            if (copy_to_user((int __user *)arg, &current_baud_rate, sizeof(int))) {
                return -EFAULT;
            }
            break;
        default:
            return -ENOTTY; // Lệnh không được hỗ trợ
    }
    return 0;
}

