#include <stdio.h>
#include <string.h>
// fgets la lenh doc tung dong lenh mot
void read_each(FILE *file, char buffer[][255], int max_lines)
{
    int temp = 0;
    while(temp < max_lines && fgets(buffer[temp], 255, file) != NULL)
    {
        temp++;
    }
}
int main()
{
    FILE *fr;
    fr = fopen("test.txt","r");
    char buffer[255][255]; int temp = 0;
    read_each(fr,buffer,255);
    for(int i = 0 ; i < 2 ; i ++)
    {
        printf("%s",buffer[i]);
    }
    printf("%lu",strlen(buffer[0]));
}