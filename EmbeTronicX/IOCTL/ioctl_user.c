#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define WR_VALUE _IOW('a','a',int32_t*)
#define RD_VALUE _IOR('a','b',int32_t*)

int main()
{
    int fd;
    int32_t value,number;
    printf("******************************\n");
    printf("**********To dep trai*********\n");

    fd = open("/dev/etx_device",O_RDWR);
    if(fd < 0)
    {
        printf("Khong the mo duoc file...\n");
        return 0;
    }

    printf("Nhap gia tri de gui \n");
    scanf("%d",&number);
    printf("Dang ghi gia tri xuong Driver\n");
    ioctl(fd,WR_VALUE,(int32_t*) &number);

    printf("Doc gia tri tu driver \n");
    ioctl(fd,RD_VALUE, (int32_t *) &value);
    printf("Gia tri %d \n",value);

    printf("Closing Driver \n");
    close(fd);


    close(fd);
}
