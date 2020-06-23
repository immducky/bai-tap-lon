//
// Created by Lang Khoang on 17-Jun-20.
//

#include <stdio.h>
#include <stdlib.h>
#include "GiaDien.h"

int main(void)
{
    enum Bac bac;
    int n = 1;
    const char *SoBac[] = {"", "1", "2", "3", "4", "5", "6"};
    GiaDien *dien_nang_TT = calloc(n, sizeof *dien_nang_TT);
    dien_nang_TT[n] = NhapGiaDien();
    //sai sai nhung ke =))
    printf("Gia cua muc tieu thu dien bac 1: %d", dien_nang_TT[0].don_gia);
    printf("\n");

    if (LuuFile(dien_nang_TT, n, "TestWrite.bin") == -1) {
        printf("Loi luu file\n");
        return 0;
    }
    int size;
    GiaDien *docSoDien = calloc(0, sizeof *docSoDien);
    size = DocFile("Test.bin", &docSoDien);
    if (size == -1) {
        printf("Loi doc file.test");
        return 0;
    }
    printf("So luong doc duoc la: %d\n", size);
    printf("Gia cua bac 1 la: %d\n", docSoDien[0].don_gia);
    printf("Ten khach hang thu 2 la: %d\n", docSoDien[0].don_gia);
    free(dien_nang_TT);
    free(docSoDien);
    return 0;
}