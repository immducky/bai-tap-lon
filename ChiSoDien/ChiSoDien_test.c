#include <stdio.h>
#include <stdlib.h>
#include "ChiSoDien.h"

int main(void)
{
    size_t n = 2;
    ChiSoDien *kh = calloc(n, sizeof *kh);
    for (int i = 0; i < n; i++) {
        do{
            kh[i] = NhapChiSoDien();
            printf("So ma khach hang la: %d\n", kh[i].ma_khach_hang);
            printf("\n");
        } while(kh[i].ma_khach_hang == -1);
    }

    if (LuuFile(kh, n, "./TestWrite.bin") == -1) {
        printf("Loi luu file\n");
        return 0;
    }

/*
 *    int size;
 *    ChiSoDien *docKH = calloc(1, sizeof *docKH);
 *    if (DocFile("./Test.bin", &docKH, &size) == -1) {
 *        printf("Loi doc file");
 *        return 0;
 *    }
 *
 *    printf("Ma so khach hang thu nhat la: %d\n", docKH[0].ma_khach_hang);
 *    printf("Ten khach hang thu 2 la: %s\n", docKH[1].chi_so_dien);
 *
 *    free(docKH);
 */

    free(kh);
    return 0;
}
