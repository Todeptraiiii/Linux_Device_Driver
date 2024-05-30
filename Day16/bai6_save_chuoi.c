#include <stdio.h>
#include <string.h>

int main()
{
    char str[100] = "to dep trai, to dep trai";
    char *str1;
    char save[50][50]; int temp = 0;
    str1 = strtok(str," ");
    while(str1 != NULL)
    {
        strcpy(save[temp],str1);
        str1 = strtok(NULL," ");
        temp++;
    }

    for(int i =0 ; i < temp; i++)
    {
        printf("%s \n",save[i]);
    }
}