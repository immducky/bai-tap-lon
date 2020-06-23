#include <stdio.h>
#include <conio.h>
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

int LuuFile(KhachHang *kh, size_t size, char ten_file[]) {
    FILE *fp = fopen(ten_file, "wb");

    if (fwrite(&size, sizeof(size_t), 1, fp) != 1) {
        printf("Loi Nhap vao khach hang\n");
        fclose(fp);
        return -1;
    }

    if (fwrite(kh, sizeof(KhachHang), size, fp) != size) {
        printf("Loi Nhap vao khach hang\n");
        fclose(fp);
        return -1;
    }

    fclose(fp);
    return 0;
}

int DocFile(char ten_file[], KhachHang **kh) {
    int n;
    FILE *file;

    file = fopen(ten_file, "rb");
    if (file == NULL) {
        printf("Loi mo file");
        return -1;
    }

    if (fread(&n, sizeof(int), 1, file) != 1) {
        printf("Loi doc file.1\n");
        return 0;
    }

    KhachHang *temp = realloc(*kh, n * sizeof(KhachHang));
    if (temp != NULL) {
        *kh = temp;
    } else {
        printf("Loi khi goi ham realloc");
        free(kh);
        exit(1);
    }
    if (fread(*kh, sizeof(KhachHang), n, file) != n) {
        printf("Loi gi do");
        return -1;
    }

    fclose(file);
    getch();
    return n;
}
