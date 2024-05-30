#include<stdio.h>
#include<ctype.h>
#include<string.h>

int main()
{
    // strcmp()         
    char c = '1';
    if (isdigit(c))
    {
        printf("Day la ki tu so \n");
    }
    else
        printf("Day khong phai ki tu so \n");
}