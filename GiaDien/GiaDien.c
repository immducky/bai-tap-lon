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

    return 0;
}

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
