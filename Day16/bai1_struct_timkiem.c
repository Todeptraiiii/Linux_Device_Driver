// De bai: Tim kiem theo ma sinh vien cho truoc

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct SinhVien
{
    char hoten[50];
    char maSV[50];
    double gpa;
};

typedef struct SinhVien SinhVien;

void timkiem(SinhVien *sv, int n, char *maSV )
{
    int temp = 0;
    for(int i = 0 ; i < n; i++)
    {
        if(!strcmp(sv[i].maSV,maSV))
        {
            temp = i;
            goto ketqua;
        }
    }
    printf("Khong tim thay ho ten sinh vien");
    ketqua :
        printf("Ho ten sinh vien nay la: %s \n",sv[temp].hoten);
        printf("GPA la: %0.2lf \n",sv[temp].gpa);
}

int main()
{
    SinhVien sv[5];
    int n = 3;
    printf("Nhap thong tin ca nhan \n");
    for(int i = 0 ; i < n ; i++)
    {
        printf("Nhap ho ten sinh vien thu : %d \n",i);
        gets(sv[i].hoten);
        printf("Nhap ma sinh vien thu : %d \n",i);
        gets(sv[i].maSV);
        scanf("%lf",&sv[i].gpa);
        getchar();

        // strcpy(sv[i].hoten,"daovanto");
        // strcpy(sv[i].maSV, "B19DCDT198");
        // sv[i].gpa = 2.5 + i;
    }

    char *chuoicantim = "b19dcdt198";

    timkiem(sv,n,chuoicantim);

    return 0;

}