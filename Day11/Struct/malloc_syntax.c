#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test(int *a, int *p)
{
    printf("%d %d ", *a, *p);
}

int main()
{
    int n = 69; int *n3;
    n3 = &n;
    char b = (char) n;
    char *a = (char*)malloc(n*sizeof(char));
    test(n3,n3);

    // int n1 = 0x12345567;
    char n1 = 'a';
    int *b1;
    b1 = malloc(sizeof(int));
    b1 = memcpy(b1,&n1,sizeof(char));

    // printf("%x ", *b1);
    // for(int i = 0; i < sizeof(int) ; i++)
    // for(int i = 0; i < sizeof(char) ; i++)
    // {
    //     // printf("byte %d of integer: %02x\n",i, (unsigned char)b1[i]);
    //     // printf("byte %d of char: %02x\n",i, (unsigned char)b1[i]);
    // }

    // for (int i = 0 ; i < sizeof(int); i ++)
    // {
    //     a[i] = 28 + i;
    // }
    for(int i =0 ; i < sizeof(int) ; i++)
    {
        // printf("%d \n",b1[i]);
    }
    // printf ("\n");
}