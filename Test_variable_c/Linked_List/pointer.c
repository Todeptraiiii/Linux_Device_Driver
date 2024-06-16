#include <stdio.h>

void trave (int *a)
{
    printf("%p \n", a);
}

int main()
{
    int a;
    a = 5;
    trave((&a));
}

