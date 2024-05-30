#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

static struct info
{
    char *hoten;
    int tuoi;
};

typedef struct info info;

static struct muonsach
{
    bool action; // 0 muon, 1 tra
    char *tensach; // loai
    info thongtin;
};
typedef struct muonsach Book;

int main()
{
    Book a; //= {a.action = "false",a.tensach = "Nhung nang con chua mong mo",
            //    a.thongtin.hoten = "Dao Van To", a.thongtin.tuoi = 18} ;
    a.action = "false";
    a.tensach = (char*)malloc(10 * sizeof(char)); // con tro thi phai cap phat bo nho
    //a.tensach = "Nhung nang cong chua mong mo"; // neu muon dung bo nho da cap phat, dung strcopy
    // strcpy(a.tensach,"Nhung nang cong chua mong mo"); // Loi error cho cap bo nho co 10 byte
    strcpy(a.tensach,"Nhung");
    a.thongtin.hoten = (char*)malloc(10*sizeof(char)); // con tro thi phai cap phat bo nho
    a.thongtin.hoten = "Dao Van To";
    a.thongtin.tuoi = 18;

    printf("Muon/Tra sach:%d \n",a.action);
    printf("Ten sach: %s \n",a.tensach);
    printf("Nguoi muon sach: %s \n", a.thongtin.hoten);
    printf("So tuoi la:%d \n",a.thongtin.tuoi);
}