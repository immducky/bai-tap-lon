#include <stdio.h>
#include <stdlib.h>
#include "GiaDien.h"
#include "../Utils/Utils.h"

int NhapGiaDien(GiaDien **dien_nang_TT) {
    GiaDien *dien_nang_TT_temp = *dien_nang_TT;
    enum Bac bac;
    const char *SoBac[] = {"", "1", "2", "3", "4", "5", "6"};
    const char *MucTieuThu[] = {"", "0 - 50", "51 - 100", "101 - 200", "201 - 300", "301 - 400", "> 400"};
    for (bac = Bac_1; bac <= Bac_6; bac++){
        printf("Nhap vao don gia cua bac %s (%s)kWh:", bac[SoBac], bac[MucTieuThu]);
        if (NhapSo(&dien_nang_TT_temp->don_gia) == -1) {
            perror("Nhap that bai");
            return -1;
        }
    }

    return dien_nang_TT_temp->don_gia;
}

int LuuFileGiaDien(GiaDien *dien_nang_TT, int n, char ten_file[]) {
    FILE *fileG = fopen(ten_file, "wb");

    if (fwrite(&n, sizeof(int), 1, fileG) != 1) {
        printf("Loi luu do dai mang\n");
        fclose(fileG);
        return -1;
    }
    if (fwrite(dien_nang_TT, sizeof(GiaDien), n, fileG) != n) {
        printf("Loi luu mang\n");
        fclose(fileG);
        return -1;
    }

    fclose(fileG);
    return 0;
}

int DocFileGiaDien(char ten_file[], GiaDien **dien_nang_TT) {
    int n;
    FILE *fileG;

    fileG = fopen(ten_file, "rb");
    if (fileG == NULL) {
        printf("Loi mo file\n");
        return -1;
    }
    if (fread(&n, sizeof(n), 1, fileG) != 1) {
        printf("Loi mo file.1");
        return -1;
    }

    GiaDien *temp = realloc(*dien_nang_TT,n * sizeof(GiaDien));
    if (temp != NULL) {
        *dien_nang_TT = temp;
    } else {
        printf("Loi khi goi ham realloc");
        free(*dien_nang_TT);
        exit(1);
    }
    if (fread(*dien_nang_TT, sizeof(GiaDien), n, fileG) != n) {
        printf("");
        return -1;
    }

    fclose(fileG);
    return n;
}

int BoSungGiaDien(GiaDien *dien_nang_TT, size_t n, char ten_file[]) {
    GiaDien *bac = calloc(0, sizeof(GiaDien));
    int size = DocFileGiaDien(ten_file, &bac);
    if (size == -1) {
        printf("Khong doc duoc du lieu tu file\n");
        return -1;
    }

    GiaDien *temp = realloc(bac, (size + n) * sizeof(GiaDien));
    if (temp != NULL) {
        bac = temp;
    } else {
        perror("Loi khi goi ham realloc: ");
        free(bac);
        exit(1);
    }

    for (int i = size; i < (size + n); i++) {
        bac[i] = dien_nang_TT[i - size];
    }
    size += n;
    if (LuuFileGiaDien(bac, size, ten_file) == -1) {
        printf("Loi khong luu duoc vao file\n");
        return -1;
    }

    free(bac);
    return 0;
}

int TimViTriBac(GiaDien *dien_nang_TT, size_t size, int bac) {
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (dien_nang_TT[mid].bac == bac) {
            return mid;
        }
        if (dien_nang_TT[mid].bac < bac) {
            left = mid + 1;
            continue;
        }

        right = mid - 1;
    }

    return -1;
}

int XoaGiaDienKhoiFile(int bac, char ten_file[]) {
    int pos;
    GiaDien *dien_nang_TT = calloc(0, sizeof(GiaDien));
    int size = DocFileGiaDien(ten_file, &dien_nang_TT);
    if (size == -1) {
        printf("Loi khi doc file\n");
        free(dien_nang_TT);
        return -1;
    }

    pos = TimViTriBac(dien_nang_TT, size, bac);
    if (pos == -1) {
        printf("Khong tim thay vi tri bac");
        free(dien_nang_TT);
        return -1;
    }

    for (int i = pos; i < size; i++) {
        dien_nang_TT[i] = dien_nang_TT[i+1];
    }
    size--;

    if (LuuFileGiaDien(dien_nang_TT, size, ten_file) == -1) {
        printf("Khong Luu vao file duoc\n");
        free(dien_nang_TT);
        return -1;
    }

    free(dien_nang_TT);
    return 0;
}

int SuaChuaGiaDien(int bac, char ten_file[] ,GiaDien dien_nang_TT) {
    int pos = -1;
    dien_nang_TT.bac = bac;
    GiaDien *file_gia_dien = (GiaDien*)calloc(0, sizeof(GiaDien));
    int size = DocFileGiaDien(ten_file, &file_gia_dien);
    if (size == -1) {
        printf("Loi doc file\n");
        free(file_gia_dien);
        return -1;
    }

    if (bac >= size || bac <= 0) {
        printf("Vi tri khong ton tai\n");
        free(file_gia_dien);
        return -1;
    }

    pos = TimViTriBac(file_gia_dien, size, bac);
    if (pos == -1) {
        printf("Khong tim thay vi tri cua bac");
        free(file_gia_dien);
        return -1;
    }

    file_gia_dien[pos] = dien_nang_TT;

    if (LuuFileGiaDien(file_gia_dien, size, ten_file) == -1) {
        printf("Khong Luu vao file duoc\n");
        free(file_gia_dien);
        return -1;
    }

    free(file_gia_dien);
    return 0;
}