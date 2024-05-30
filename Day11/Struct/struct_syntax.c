#include <stdio.h>
#include <string.h>

typedef char c8[100];

struct info 
{
    c8 hoten; // tai sao con tro thi lai duoc
    c8 email; // tai sao con tro thi lai duoc ma email thi lai khong
    int tuoi;
}__attribute__((packed));

typedef struct info Person;

int main()
{
    Person a,*b;
    a.email = 'daovanto@gmail.com';
    a.hoten = 'todeptrai';
    a.tuoi = 22;
    b = &a;
    printf ("%s %s %d \n",a.email,a.hoten,a.tuoi);
    // printf ("%s %s %d \n",b->email,b->hoten,b->tuoi);
}