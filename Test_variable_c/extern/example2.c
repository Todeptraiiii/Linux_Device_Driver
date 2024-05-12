#include <stdio.h>

extern int a;

void using_extern(void)
{
	printf("%d \n",a);
}
