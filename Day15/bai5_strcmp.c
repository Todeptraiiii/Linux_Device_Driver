#include <stdio.h>
#include <string.h>

int main()
{
    char *str1, *str2;
    str1 = "daovanto";
    str2 = "daovanto";
    if(!strcmp(str1,str2))
    {
        printf("Hai chuoi giong nahu \n");
    }
    else
    {
        printf ("Hai chuoi khong giong nhau \n");
    }
}