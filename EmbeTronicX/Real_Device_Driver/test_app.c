#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int8_t write_buf[1024];
int8_t read_buf[1024];

int main()
{
    int fd;
    char option;
    printf("******************************\n");
    printf("**********To dep trai*********\n");

    fd = open("/dev/etx_device",O_RDWR);
    if(fd < 0)
    {
        printf("Khong the mo duoc file...\n");
        return 0;
    }

    while(1)
    {
        printf("****Hay nhap lua chon cua ban****\n");
        printf("            1. Write             \n");
        printf("            2. Read              \n");
        printf("            3. Exit              \n");
        printf("*********************************\n");
        scanf(" %c",&option);
        printf("Lua chon cua ban la = %c \n", option);

        switch(option)
        {
            case '1':
                printf("Nhap chuoi ban muon ghi : ");
                scanf(" %s",write_buf);
                printf("Data Writing....");
                write(fd,write_buf,strlen(write_buf)+1);
                printf("Done!\n");
                break;
            case '2':
                printf("Data Reading...");
                read(fd, read_buf,1024);
                printf("Done!\n\n");
                printf("Data = %s \n\n",read_buf);
                break;
            case '3':
                close(fd);
                exit(1);
                break;
            default:
                printf("Nhap gia tri hop le: %c \n",option);
                break;
        }
    }
    close(fd);
}
