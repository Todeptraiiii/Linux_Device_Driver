#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int dst[6];
    int src[6];
    int proto[2];
} Mac_head;

static void in(Mac_head *x)
{
    char buffer[100]; // Tạo bộ đệm để đọc dữ liệu đầu vào
    printf("Nhap dst (6 số nguyên cách nhau bởi dấu cách): \n");
    if (fgets(buffer, sizeof(buffer), stdin)) {
        sscanf(buffer, "%d %d %d %d %d %d", &x->dst[0], &x->dst[1], &x->dst[2], &x->dst[3], &x->dst[4], &x->dst[5]);
    }

    printf("Nhap src (6 số nguyên cách nhau bởi dấu cách): \n");
    if (fgets(buffer, sizeof(buffer), stdin)) {
        sscanf(buffer, "%d %d %d %d %d %d", &x->src[0], &x->src[1], &x->src[2], &x->src[3], &x->src[4], &x->src[5]);
    }

    printf("Nhap proto (2 số nguyên cách nhau bởi dấu cách): \n");
    if (fgets(buffer, sizeof(buffer), stdin)) {
        sscanf(buffer, "%d %d", &x->proto[0], &x->proto[1]);
    }
}

int main()
{
    Mac_head m;
    in(&m);
    for (int i = 0; i < 6; i++)
    {
        printf("%d \n", m.dst[i]);
    }
    return 0;
}
