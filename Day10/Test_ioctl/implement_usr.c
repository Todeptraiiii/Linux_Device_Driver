#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "my_ioctl.h"

int main() {
    int fd = open("/dev/mydevice", O_RDWR);
    if (fd < 0) {
        perror("Failed to open the device");
        return EXIT_FAILURE;
    }

    // Reset thiết bị
    if (ioctl(fd, MY_IOCTL_RESET) < 0) {
        perror("Failed to reset the device");
        close(fd);
        return EXIT_FAILURE;
    }

    // Thiết lập tốc độ baud
    int new_baud_rate = 115200;
    if (ioctl(fd, MY_IOCTL_SET_BAUD, &new_baud_rate) < 0) {
        perror("Failed to set baud rate");
        close(fd);
        return EXIT_FAILURE;
    }

    // Lấy tốc độ baud hiện tại
    int current_baud_rate;
    if (ioctl(fd, MY_IOCTL_GET_BAUD, &current_baud_rate) < 0) {
        perror("Failed to get baud rate");
        close(fd);
        return EXIT_FAILURE;
    }

    printf("Current baud rate: %d\n", current_baud_rate);

    close(fd);
    return EXIT_SUCCESS;
}

