#include <stdio.h>

extern void using_extern();

int a = 5 ;

int main()
{
	a = a + 1;
	using_extern();
}
