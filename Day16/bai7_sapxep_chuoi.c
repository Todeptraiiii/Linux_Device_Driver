#include <stdio.h>
#include <string.h>

void sapxepchuoi(char a[][50] , int n)
{
    for(int i = 0 ; i < n; i++)
    {
        int max_int = i;
        for(int j = i + 1 ; j < n; j++ )
        {
            if(strcmp(a[j],a[max_int]) < 0)
            {
                max_int = j;
            }
        }
        char temp[50];
        strcpy(temp,a[i]);
        strcpy(a[i],a[max_int]);
        strcpy(a[max_int],temp);
    }
}

int main()
{
    char str[100] = "dao van to dep trai nhat tan hoi";
    char save[50][50], *str1;
    int temp = 0;
    str1 = strtok(str," ");
    while(str1 != NULL)
    {
        strcpy(save[temp],str1);
        str1 = strtok(NULL," ");
        temp ++;
    }

    sapxepchuoi(save,temp);
    for(int i = 0 ; i < temp ; i ++)
    {
        printf("%s ",save[i]);
    }
        printf("\n");

}