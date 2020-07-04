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
            printf("Nhap that bai\n");
            return chi_so;
        }
    }

    printf("Nhap vao cac so ky: ");
    if (NhapSo(&num) == -1) {
        chi_so.ky_thu_phi = ky_loi;
        printf("Nhap that bai\n");
        return chi_so;
    }

    if (num == ky_loi) {
        chi_so.ky_thu_phi = ky_loi;
        printf("Nhap that bai\n");
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

int DocFileChiSoDien(char ten_file[], ChiSoDien **chi_so) {
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

int BoSungChiSoDien(ChiSoDien *chi_so, size_t n, char ten_file[]) {
    ChiSoDien *KH_tu_file = calloc(0, sizeof(ChiSoDien));
    int size = DocFileChiSoDien(ten_file, &KH_tu_file);
    if (size == -1) {
        printf("Khong doc duoc du lieu tu file\n");
        return -1;
    }

    ChiSoDien *temp = realloc(KH_tu_file, (size + n) * sizeof(ChiSoDien));
    if (temp != NULL) {
        KH_tu_file = temp;
    } else {
        perror("Loi khi goi ham realloc: ");
        free(KH_tu_file);
        exit(1);
    }

    for (int i = size; i < (size + n); i++) {
        KH_tu_file[i] = chi_so[i - size];
    }
    size += n;
    if (LuuFileChiSoDien(KH_tu_file, size, ten_file) == -1) {
        printf("Loi khong luu duoc vao file\n");
        return -1;
    }

    free(KH_tu_file);;
    return 0;
}

int TimViTriChiSoDien(ChiSoDien *chi_so, size_t size, int ma_khach_hang) {
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (chi_so[mid].ma_khach_hang == ma_khach_hang) {
            return mid;
        }

        if (chi_so[mid].ma_khach_hang < ma_khach_hang) {
            left = mid + 1;
            continue;
        }

        right = mid - 1;
    }

    return -1;
}

int XoaChiSoDienKhoiFile(int ma_khach_hang, char ten_file[]) {
    int pos;
    ChiSoDien *chi_so = calloc(0, sizeof(ChiSoDien));
    int size = DocFileChiSoDien(ten_file, &chi_so);
    if (size == -1) {
        printf("Loi khi doc file\n");
        free(chi_so);
        return -1;
    }

    pos = TimViTriChiSoDien(chi_so, size, ma_khach_hang);
    if (pos == -1) {
        printf("Khong tim thay vi tri khac hang");
        free(chi_so);
        return -1;
    }

    for (int i = pos; i < size; i++) {
        chi_so[i] = chi_so[i+1];
    }
    size--;

    if (LuuFileChiSoDien(chi_so, size, ten_file) == -1) {
        printf("Khong Luu vao file duoc\n");
        free(chi_so);
        return -1;
    }

    free(chi_so);
    return 0;
}

int SuaChuaChiSoDien(int ma_khach_hang, char ten_file[] ,ChiSoDien chi_so) {
    int pos = -1;
    chi_so.ma_khach_hang = ma_khach_hang;
    ChiSoDien *file_khach_hang = (ChiSoDien*)calloc(0, sizeof(ChiSoDien));
    int size = DocFileChiSoDien(ten_file, &file_khach_hang);
    if (size == -1) {
        printf("Loi doc file\n");
        free(file_khach_hang);
        return -1;
    }

    if (ma_khach_hang >= size || ma_khach_hang <= 0) {
        printf("Vi tri khong ton tai\n");
        free(file_khach_hang);
        return -1;
    }

    pos = TimViTriChiSoDien(file_khach_hang, size, ma_khach_hang);
    if (pos == -1) {
        printf("Khong tim thay vi tri khac hang");
        free(file_khach_hang);
        return -1;
    }

    file_khach_hang[pos] = chi_so;

    if (LuuFileChiSoDien(file_khach_hang, size, ten_file) == -1) {
        printf("Khong Luu vao file duoc\n");
        free(file_khach_hang);
        return -1;
    }

    free(file_khach_hang);
    return 0;
}

int KiemTraKyHopLe(int thang) {
    if (thang <= 0 || thang > 12) {
        return 0;
    }

    return 1;
}

int TinhDienNangTieuThu(char ten_file[], int ma_khach_hang, int thang) {
    int pos;
    int dien_nang_TT;

    if (KiemTraKyHopLe(thang)) {
        printf("Nhap vao thang khong dung");
        return -1;
    }

    ChiSoDien *chi_so = calloc(0, sizeof(ChiSoDien));
    int size = DocFileChiSoDien(ten_file, &chi_so);
    if (size == -1) {
        printf("Khong doc duoc file tien dien");
        return -1;
    }

    pos = TimViTriChiSoDien(chi_so, size, ma_khach_hang);
    if (pos == -1) {
        printf("Khong tim thay vi tri khac hang");
        free(chi_so);
        return -1;
    }

    if (thang-1 == ky1) {
        free(chi_so);
        return chi_so[pos].chi_so_dien[0];
    }

    dien_nang_TT = chi_so[pos].chi_so_dien[thang-1] - chi_so[pos].chi_so_dien[thang-2];
    free(chi_so);
    return dien_nang_TT;
}
