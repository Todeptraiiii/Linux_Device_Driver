#include<stdio.h>

int main()
{
    int n = 28;
    if(n%2 == 0)
    {
        goto in;
    }
    printf("So nay khong chia het cho 2 \n");
    in:
    printf("So nay chia het cho 2 \n");
}