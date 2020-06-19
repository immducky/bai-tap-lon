#include <stdio.h>
#include <stdlib.h>
#include "KhachHang.h"
#include "../Utils/Utils.h"

int MaKhachHang = 1;

KhachHang NhapKhachHang() {
    KhachHang kh;
    kh.ma_khach_hang = -1;

    printf("Nhap vao ten khach hang: ");
    fgets(kh.ten, 100, stdin);

    printf("Nhap vao dia chi khach hang: ");
    fgets(kh.dia_chi, 100, stdin);

    printf("Nhap vao so cong to: ");
    if (NhapSo(&kh.ma_cong_to) == -1) {
        printf("Nhap that bai");
        return kh;
    };

    kh.ma_khach_hang = MaKhachHang;
    MaKhachHang++;

    return kh;
}

int LuuFile(KhachHang *kh, int n, char ten_file[]) {
    FILE *fp = fopen(ten_file, "wb");

    if (fwrite(&n, sizeof(int), 1, fp) != 1) {
        printf("Loi Nhap vao khach hang\n");
        fclose(fp);
        return -1;
    }

    if (fwrite(kh, sizeof(KhachHang), n, fp) != n) {
        printf("Loi Nhap vao khach hang\n");
        fclose(fp);
        return -1;
    }

    fclose(fp);
    return 0;
}

int DocFile(KhachHang **kh, int *n, char ten_file[]) {
    FILE *fp = fopen(ten_file, "rb");

    if (fp == NULL) {
        printf("Khong mo duoc file de doc\n");
        return 1;
    }

    if (fread(&n, sizeof(*n), 1, fp) != 1) {
        printf("Loi doc so luong\n");
        return 1;
    }

    KhachHang *temp = realloc(*kh, *n * sizeof(KhachHang));
    if (temp != NULL) {
        *kh = temp;
    } else {
        printf("Loi khi goi ham realloc\n");
        free(kh);
        exit(1);
    }
    if (fread(*kh, sizeof(KhachHang), *n, fp) != *n) {
        printf("Loi doc khach hang\n");
        return -1;
    }

    fclose(fp);

    return 0;
}
