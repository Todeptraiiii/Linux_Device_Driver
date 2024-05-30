#include <stdio.h>

int main()
{
    int M = 5;
    int *N = &M;

    printf("Dia chi cua M: %p \n",&M);
    printf("Dia chi cua N: %p \n",&N);
    printf("Gia tri cua N: %d \n",*N);
}