//
// Created by Lang Khoang on 17-Jun-20.
//

#include <stdio.h>
#include <stdlib.h>
#include "GiaDien.h"

int main(void)
{
    enum Bac bac;
    int n = 6;
    const char *SoBac[] = {"", "1", "2", "3", "4", "5", "6"};
    GiaDien *dien_nang_TT = calloc(n, sizeof *dien_nang_TT);
    NhapGiaDien(&dien_nang_TT);

    int size = LuuFileGiaDien(dien_nang_TT, n, "./TestWrite.bin");
    if (size == -1) {
        perror("Loi luu file\n");
        return 0;
    }

    GiaDien *temp = calloc(0, sizeof *temp);
    size = DocFileGiaDien("./Test.bin", &temp);
    printf("So luong doc duoc la: %d\n", size);
    printf("Gia dien so 1 la: %.3f\n", temp->don_gia[2]);

    float result = TinhTienDien("./Test.bin", 45);
    printf("Gia dien tai 45 la: %.3f\n", result);

    free(temp);
    free(dien_nang_TT);
    return 0;
}
