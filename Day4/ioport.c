#include <linux/ioport.h>
#include <linux/errno.h>

static int skull_detect(unsigned int port, unsigned int range)
{
    int err;
    
    // Kiểm tra xem phạm vi cổng được yêu cầu có sẵn không
    if ((err = check_region(port, range)) < 0)
        return err; // Phạm vi cổng đang bận
    
    // Kiểm tra xem phần cứng có tồn tại tại các cổng được chỉ định không
    if (skull_probe_hw(port, range) != 0)
        return -ENODEV; // Phần cứng không được tìm thấy
    
    // Cấp phát các cổng
    request_region(port, range, "skull"); // "Không thể thất bại"

    return 0; // Thành công
}

