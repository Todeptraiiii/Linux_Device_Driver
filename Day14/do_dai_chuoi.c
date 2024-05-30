// #include <stdio.h>
// #include <string.h>

// int main()
// {
//     char str[] = "Hello, world!";
//     size_t length = strlen(str); // Tính độ dài chuỗi

//     printf("Độ dài của chuỗi: %zu\n", length);

//     return 0;
// }
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printString(const char *str)
{
    printf("Chuỗi: %s\n", str);
    printf("Độ dài của chuỗi: %zu\n", strlen(str));
}

void printArray(int *arr, int size)
{
    printf("Mảng số nguyên: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    // Xử lý chuỗi ký tự
    char str[] = "Hello, world!";
    printString(str);

    // Xử lý mảng số nguyên
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    printArray(arr, size);

    return 0;
}
