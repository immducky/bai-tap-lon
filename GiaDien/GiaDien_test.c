//
// Created by Administrator on 17-Jun-20.
//

#include <stdio.h>
#include <stdlib.h>
#include "GiaDien.h"

int main(void)
{
    size_t n = 2;
    GiaDien *dien_nang_TT = calloc(n, sizeof *dien_nang_TT);
    for (int i = 0; i < n; i++) {
        do{
            dien_nang_TT[i] = NhapGiaDien();
            printf("So dien nang tieu thu la: %d\n", dien_nang_TT[i].so_dien_nang_tieu_thu);
            printf("\n");
        } while(dien_nang_TT[i].so_dien_nang_tieu_thu == -1);
    }

    if (LuuFile(dien_nang_TT, n, "./TestWrite.bin") == -1) {
        printf("Loi luu file\n");
        return 0;
    }
    free(dien_nang_TT);
    return 0;
}