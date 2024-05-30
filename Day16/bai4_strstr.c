// ham tra ve vi tri chuoi dau tien duoc tim thay
#include <stdio.h>
#include <string.h>

int main()
{
    char str1[100], str2[100];
    strcpy(str1,"daovan to dep trai to dep trai");
    strcpy(str2, "to");

    char *res;
    res = strstr(str1,str2);

    printf("%d \n", res - str1); // tai sao res - str1
    // Becasue : res luu dia chi trung dau tien, str1 luu dia chi bat dau chuoi
    // Lay dau tien xuat hien - bat dau = vi tri trung trong chuoi
}