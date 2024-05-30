#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned int u2;
typedef struct header_file MAC;

static struct header_file
{
    u2 src[6];
    u2 dst[6];
    u2 proto[2];
};


int main()
{
    MAC a = {   .src    = {0x56,0x57,0x56,0x56,0x57,0x105}, 
                .dst    = {0xAB,0xBC,0xAA,0xAB,0xBC,0xAA},
                .proto  = {0x08,0x00}
            };
    
    // Ep kieu de in mot phat
    char *str = &a;
    for(int i =0 ; i< sizeof(a); i++)
    {
        printf("Byte[%d]: %c (0x%x) \n",i,str[i],(unsigned char) (str[i]));
    }
}