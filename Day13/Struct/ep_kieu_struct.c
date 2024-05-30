#include <stdio.h>

typedef struct {
    int id;
    char name[20];
    float salary;
} Employee;

int main() {
    Employee emp = {1, "John Doe", 5000.0};

    // Ép kiểu struct về int*
    int *intPtr = (int*)&emp;

    // In giá trị int đầu tiên từ struct
    printf("ID: %d\n", *intPtr);

    // Ép kiểu struct về char*
    char *charPtr = (char*)&emp;

    // In các byte đầu tiên từ struct dưới dạng ký tự
    for (int i = 0; i < sizeof(emp); i++) {
        printf("Byte %d: %c (0x%x)\n", i, charPtr[i], (unsigned char)charPtr[i]);
    }

    return 0;
}
