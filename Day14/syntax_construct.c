#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Thêm thư viện này để sử dụng strcpy

typedef struct 
{
    char *hoten; // Thay đổi kiểu từ mảng char sang con trỏ char
    int *tuoi;
} thongtin;

int main()
{
    thongtin a;
    a.tuoi = (int*)malloc(sizeof(int));
    if (a.tuoi == NULL) {
        printf("Cấp phát bộ nhớ thất bại\n");
        return 1;
    }
    *(a.tuoi) = 22;

    a.hoten = (char*)malloc(9 * sizeof(char)); // Cấp phát bộ nhớ cho 8 ký tự cộng với ký tự null '\0'
    if (a.hoten == NULL) {
        printf("Cấp phát bộ nhớ cho hoten thất bại\n");
        free(a.tuoi); // Giải phóng bộ nhớ đã cấp phát trước khi thoát
        return 1;
    }

    strcpy(a.hoten, "abcdefgh ijklm"); // Sao chép chuỗi vào bộ nhớ đã cấp phát

    // In chuỗi hoten và tuổi
    printf("Họ tên: %s\n", a.hoten);
    printf("Tuổi: %d\n", *(a.tuoi));

    // Đừng quên giải phóng bộ nhớ đã cấp phát
    free(a.hoten);
    free(a.tuoi);

    return 0;
}
