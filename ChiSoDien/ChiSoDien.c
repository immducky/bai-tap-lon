#include <stdio.h>
#include <stdlib.h>
#include "ChiSoDien.h"
#include "../Utils/Utils.h"
#include "../GiaDien/GiaDien.h"

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

    for (int i = 0; i < 12; i++) {
        printf("Nhap vao ngay chot dien %d: ", i+1);
        if (NhapSo(&chi_so.ngay_chot_chi_so[i]) == -1) {
            chi_so.ky_thu_phi = ky_loi;
            printf("Nhap that bai");
            return chi_so;
        }
    }

    for (int i = 0; i < 12; i++) {
        printf("Nhap vao chi so dien ky %d: ", i+1);
        if (NhapSo(&chi_so.chi_so_dien[i]) == -1) {
            chi_so.ky_thu_phi = ky_loi;
            printf("Nhap that bai");
            return chi_so;
        }
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

int LuuFileChiSoDien(ChiSoDien *chi_so, int n, char ten_file[]) {
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

int DocFileKhachHang(char ten_file[], ChiSoDien **chi_so) {
    int n;
    FILE *file;

    file = fopen(ten_file, "rb");
    if (file == NULL) {
        printf("");
        return -1;
    }
    if (fread(&n, sizeof(n), 1, file) != 1) {
        printf("");
        return -1;
    }

    ChiSoDien *temp = realloc(*chi_so, n * sizeof(ChiSoDien));
    if (temp == NULL) {
        printf("Loi chi_soi goi ham realloc");
        free(*chi_so);
        exit(1);
    } else {
        *chi_so = temp;
    }
    if (fread(*chi_so, sizeof(ChiSoDien), n, file) != n) {
        printf("Loi khi viet vao chi_o");
        return -1;
    }

    fclose(file);
    return n;
}

int KiemTraKyHopLe(int thang) {
    if (thang <= 0 || thang > 12) {
        return 0;
    }

    return 1;
}

int TinhDienNangTieuThu(ChiSoDien *chi_so, int ma_khach_hang, int thang) {
    if (KiemTraKyHopLe(thang)) {
        printf("Nhap vao thang khong dung");
        return -1;
    }

    if (thang == ky1) {
        return
    }

}

