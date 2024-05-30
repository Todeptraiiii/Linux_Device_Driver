/*
* phạm vi cổng: thiết bị có thể nằm giữa
* 0x280 và 0x300, với bước nhảy là 0x10. Nó sử dụng 0x10 cổng.
*/
#define SKULL_PORT_FLOOR 0x280
#define SKULL_PORT_CEIL 0x300
#define SKULL_PORT_RANGE 0x010

/* 
* hàm dưới đây thực hiện tự động phát hiện, trừ khi một giá trị cụ thể được gán bởi insmod cho "skull_port_base"
*/
static int skull_port_base = 0; /* 0 đặt cấu hình tự động */
MODULE_PARM(skull_port_base, "i");
MODULE_PARM_DESC(skull_port_base, "Base I/O port for skull");

static int skull_find_hw(void) /* trả về số lượng thiết bị */
{
    /* base là giá trị được gán vào thời điểm tải hoặc thử nghiệm đầu tiên */
    int base = skull_port_base ? skull_port_base : SKULL_PORT_FLOOR;
    int result = 0;

    /* lặp một lần nếu giá trị được gán; thử tất cả nếu tự động phát hiện */
    do {
        if (skull_detect(base, SKULL_PORT_RANGE) == 0) {
            skull_init_board(base);
            result++;
        }
        base += SKULL_PORT_RANGE; /* chuẩn bị cho thử nghiệm tiếp theo */
    } while (skull_port_base == 0 && base < SKULL_PORT_CEIL);

    return result;
}

