#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct 
{
    char *hoten;
    double gpa;
} info;

int main()
{
    info s;
    strcpy(s.hoten,"Dao Van To"); // se co luc bi loi bo nho neu k duoc cap phat
    printf("%s", s.hoten);
    return 0;
}