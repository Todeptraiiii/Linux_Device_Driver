/* SPDX-License-Identifier: GPL-2.0 */
#ifndef MY_IOCTL_H
#define MY_IOCTL_H

#include <linux/ioctl.h>

// Chọn một số ma thuật duy nhất
#define MY_IOCTL_MAGIC 'k'

// Định nghĩa các lệnh ioctl
#define MY_IOCTL_RESET _IO(MY_IOCTL_MAGIC, 0)                   // Không có dữ liệu
#define MY_IOCTL_SET_BAUD _IOW(MY_IOCTL_MAGIC, 1, int)          // Truyền một giá trị int
#define MY_IOCTL_GET_BAUD _IOR(MY_IOCTL_MAGIC, 2, int)          // Nhận một giá trị int

#endif // MY_IOCTL_H

