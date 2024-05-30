#include <stdio.h>
#include <stdlib.h>

int main() {
    char str1[] = "1234";
    char str2[] = "0x1A3F";
    char str3[] = "0754";
    char str4[] = "1101";
    char *endptr;
    long int num;

    // Chuyển đổi chuỗi thập phân
    num = strtol(str1, &endptr, 10);
    printf("Chuỗi: %s -> Số thập phân: %ld\n", str1, num);

    // Chuyển đổi chuỗi thập lục phân
    num = strtol(str2, &endptr, 16);
    printf("Chuỗi: %s -> Số thập lục phân: %lx\n", str2, num);

    // Chuyển đổi chuỗi bát phân
    num = strtol(str3, &endptr, 8);
    printf("Chuỗi: %s -> Số bát phân: %ld\n", str3, num);

    // Chuyển đổi chuỗi nhị phân
    num = strtol(str4, &endptr, 2);
    printf("Chuỗi: %s -> Số nhị phân: %ld\n", str4, num);

    return 0;
}
