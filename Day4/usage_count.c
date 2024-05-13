#include <linux/module.h>
#include <linux/kernel.h>

// Cấu trúc dữ liệu đại diện cho một module đơn giản
struct my_module_data {
    int data;
};

struct my_module_data *module_data = NULL;

// Hàm khởi tạo module
int init_module(void) {
    int err = 0;

    // Cấp phát bộ nhớ cho cấu trúc dữ liệu của module
    module_data = kmalloc(sizeof(struct my_module_data), GFP_KERNEL);
    if (!module_data) {
        printk(KERN_ERR "Failed to allocate memory for module data\n");
        err = -ENOMEM; // Lỗi không đủ bộ nhớ
        goto fail;
    }

    // Khởi tạo dữ liệu cho module
    module_data->data = 42;

    // Tăng số lần sử dụng của module
    MOD_INC_USE_COUNT;

    printk(KERN_INFO "Module initialized\n");
    return 0; // Khởi tạo thành công

fail:
    // Gọi cleanup_module để giải phóng tài nguyên
    cleanup_module();
    return err; // Trả về mã lỗi
}

// Hàm giải phóng tài nguyên của module
void cleanup_module(void) {
    // Giảm số lần sử dụng của module
    MOD_DEC_USE_COUNT;

    // Kiểm tra xem module có còn được sử dụng hay không
    if (!MOD_IN_USE) {
        // Nếu không còn ai sử dụng module, giải phóng bộ nhớ và thông báo
        if (module_data) {
            kfree(module_data);
            module_data = NULL;
        }
        printk(KERN_INFO "Module resources released\n");
    } else {
        printk(KERN_INFO "Module still in use\n");
    }
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");

