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
    printf("Gia cua muc tieu thu dien bac 1: %d", dien_nang_TT[n].don_gia);
    printf("\n");

    if (LuuFile(dien_nang_TT, n, "./TestWrite.bin") == -1) {
        printf("Loi luu file\n");
        return 0;
    }
    free(dien_nang_TT);
    return 0;
}