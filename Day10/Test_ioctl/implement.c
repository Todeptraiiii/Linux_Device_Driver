#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include "my_ioctl.h"

// Hàm ioctl của trình điều khiển
static long my_device_ioctl(struct file *filp, unsigned int cmd, unsigned long arg) {
    switch(cmd) {
        case MY_IOCTL_RESET:
            // Reset thiết bị
            printk(KERN_INFO "Device reset\n");
            break;
        case MY_IOCTL_SET_BAUD:
            // Thiết lập tốc độ baud
            {
                int baud_rate;
                if (copy_from_user(&baud_rate, (int __user *)arg, sizeof(int))) {
                    return -EFAULT;
                }
                printk(KERN_INFO "Setting baud rate to %d\n", baud_rate);
                // Thiết lập tốc độ baud cho thiết bị
            }
            break;
        case MY_IOCTL_GET_BAUD:
            // Lấy tốc độ baud hiện tại
            {
                int current_baud_rate = 9600; // Giả sử tốc độ baud hiện tại
                if (copy_to_user((int __user *)arg, &current_baud_rate, sizeof(int))) {
                    return -EFAULT;
                }
                printk(KERN_INFO "Current baud rate: %d\n", current_baud_rate);
            }
            break;
        default:
            return -ENOTTY; // Lệnh không được hỗ trợ
    }
    return 0;
}

static struct file_operations fops = {
    .unlocked_ioctl = my_device_ioctl,
    // Các phương thức khác
};

