#include <string.h>
#include <stdio.h>

int main()
{
    char str1[100] = "dao van to dep trai vcl";
    char *tach; int *i; int i1;
    // i1 = 1;
    // i = &i1;
    // // giai tham chieu
    // printf("%d \n",*i);
    printf("%s\n",tach);
     tach= strtok(str1," ");
    int i = 0;

    while(tach != NULL)
    {
        i ++;
        printf("Chuoi dau tien [%d]: %s \n",i,tach);
        tach = strtok(NULL," ");
    }
}