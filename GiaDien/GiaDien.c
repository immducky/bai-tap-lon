#include <stdio.h>
#include <stdlib.h>
#include "GiaDien.h"
#include "../Utils/Utils.h"

GiaDien NhapGiaDien() {
    GiaDien dien_nang_TT;
    printf("Nhap vao so dien nang tieu thu: ");
    if (NhapSo(&dien_nang_TT.so_dien_nang_tieu_thu) == -1) {
        printf("Nhap that bai");
        return dien_nang_TT;
    };
    printf("Nhap vao don gia: ");
    if (NhapSo(&dien_nang_TT.don_gia) == -1) {
        printf("Nhap that bai");
        return dien_nang_TT;
    };
    return dien_nang_TT;
}

/*
GiaDien BangGia(){
    GiaDien dien_nang_TT;
    if ()
} */

int LuuFile(GiaDien *dien_nang_TT, int n, char ten_file[]) {
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

int DocFile(char ten_file[], GiaDien **dien_nang_TT, int *n) {
    FILE *fileG;

    fileG = fopen(ten_file, "rb");
    if (fileG == NULL) {
        printf("Loi mo file");
        return -1;
    }
    if (fread(&n, sizeof(*n), 1, fileG) != 1) {
        printf("Loi mo file");
        return -1;
    }

    GiaDien *temp = realloc(*dien_nang_TT, *n * sizeof(GiaDien));
    if (temp != NULL) {
        *dien_nang_TT = temp;
    } else {
        printf("Loi khi goi ham realloc");
        free(*dien_nang_TT);
        exit(1);
    }
    if (fread(*dien_nang_TT, sizeof(GiaDien), *n, fileG) != *n) {
        printf("");
        return -1;
    }

    fclose(fileG);
    return 0;
}

