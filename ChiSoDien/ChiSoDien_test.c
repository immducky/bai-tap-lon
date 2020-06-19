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

    int size;
    ChiSoDien *docKH = calloc(0, sizeof *docKH);
    size = DocFile("./Test.bin", &docKH);
    if (size == -1) {
        printf("Loi doc file");
        return 0;
    }

    printf("So luong doc duoc la: %d\n", size);
    printf("Ma so khach hang thu nhat la: %d\n", docKH[0].ma_khach_hang);
    printf("Ten khach hang thu 2 la: %d\n", docKH[1].ma_khach_hang);

    free(docKH);

    free(kh);
    return 0;
}
