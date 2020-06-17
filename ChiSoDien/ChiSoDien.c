#include <stdio.h>
#include <stdlib.h>
#include "ChiSoDien.h"
#include "../Utils/Utils.h"

enum ky DoiSoThanhKy(int num) {
    switch (num) {
        case 1:
            return ky1;
        case 2:
            return ky2;
        case 3:
            return ky3;
        case 4:
            return ky4;
        case 5:
            return ky5;
        case 6:
            return ky6;
        case 7:
            return ky7;
        case 8:
            return ky8;
        case 9:
            return ky9;
        case 10:
            return ky10;
        case 11:
            return ky11;
        case 12:
            return ky12;
        default:
            printf("Loi khong co ky do");
            return ky_loi;
    }
}

ChiSoDien NhapChiSoDien() {
    int num;
    enum ky ky_thu_phi;
    ChiSoDien chi_so;

    printf("Nhap vao ma so khach hang: ");
    if (NhapSo(&chi_so.ma_khach_hang) == -1) {
        chi_so.ky_thu_phi = ky_loi;
        printf("Nhap that bai");
        return chi_so;
    }

    printf("Nhap vao ngay chot dien: ");
    if (NhapSo(&chi_so.ngay_chot_chi_so) == -1) {
        chi_so.ky_thu_phi = ky_loi;
        printf("Nhap that bai");
        return chi_so;
    }

    printf("Nhap vao chi so dien: ");
    if (NhapSo(&chi_so.chi_so_dien) == -1) {
        chi_so.ky_thu_phi = ky_loi;
        printf("Nhap that bai");
        return chi_so;
    }

    printf("Nhap vao cac so ky: ");
    if (NhapSo(&num) == -1) {
        chi_so.ky_thu_phi = ky_loi;
        printf("Nhap that bai");
        return chi_so;
    }
    ky_thu_phi = DoiSoThanhKy(num);
    if (ky_thu_phi == ky_loi) {
        chi_so.ky_thu_phi = ky_loi;
        printf("Nhap that bai");
        return chi_so;
    }

    return chi_so;
}

int LuuFile(ChiSoDien *chi_so, int n, char ten_file[]) {
    FILE *file = fopen(ten_file, "wb");

    if (fwrite(&n, sizeof(int), 1, file) != 1) {
        printf("Loi luu do dai mang\n");
        fclose(file);
        return -1;
    }
    if (fwrite(chi_so, sizeof(ChiSoDien), n, file) != n) {
        printf("Loi luu mang\n");
        fclose(file);
        return -1;
    }

    fclose(file);
    return 0;
}

int DocFile(char ten_file[], ChiSoDien **chi_so, int *n) {
    FILE *file;

    file = fopen(ten_file, "rb");
    if (file == NULL) {
        printf("");
        return -1;
    }
    if (fread(n, sizeof(*n), 1, file) != 1) {
        printf("");
        return -1;
    }

    ChiSoDien *temp = realloc(*chi_so, *n * sizeof(ChiSoDien));
    if (temp == NULL) {
        printf("Loi chi_soi goi ham realloc");
        free(*chi_so);
        exit(1);
    } else {
        *chi_so = temp;
    }
    if (fread(*chi_so, sizeof(ChiSoDien), *n, file) != *n) {
        printf("");
        return -1;
    }

    fclose(file);
    return 0;
}
