#include <stdio.h>
#include <string.h>
// De bai: Sap xep sinh vien theo gpa giam dan

struct SinhVien
{
    char hoten[50];
    char lop[50];
    double gpa;
};
typedef struct SinhVien SinhVien;

void sapxep (SinhVien s[], int n)
{
    
    for(int i = 0 ; i < n ; i++)
    {
        int max_idx = i;
        for(int j = i + 1; j < n; j ++)
        {
            // so sanh thuoc tinh gi
            if(s[j].gpa > s[max_idx].gpa)
            {
                max_idx = j;
            }
        }
        SinhVien tmp = s[i];
        s[i] = s[max_idx];
        s[max_idx] = tmp;
    }
}

int main()
{
    SinhVien a[100];
    int n = 3;
    for (int i = 0 ; i < n ; i++)
    {
        strcpy(a[i].hoten,"daovanto");
        strcpy(a[i].lop, "12A7");
        a[i].gpa = 2.8 + i;
    }
    sapxep(a,n);
    for(int i = 0; i < n; i++)
    {
        printf("Thong tin : %f \n", a[i].gpa);
    }
    return 0;
}