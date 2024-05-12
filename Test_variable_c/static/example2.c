#include <stdio.h>

extern void test_static(int i);

int main()
{
	test_static(1);
	test_static(3);
}
