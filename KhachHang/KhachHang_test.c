#include <stdio.h>
#include <stdlib.h>
#include "KhachHang.h"
#include <conio.h>

int main(void)
{
    size_t n = 2;
    KhachHang *kh = calloc(n, sizeof *kh);
    for (int i = 0; i < n; i++) {
        do{
            kh[i] = NhapKhachHang();
            printf("So ma khach hang la: %d\n", kh[i].ma_khach_hang);
            printf("\n");
        } while(kh[i].ma_khach_hang == -1);
    }

    if (LuuFile(kh, n, "TestWrite.bin") == -1) {
        printf("Loi luu file");
        return 0;
    }

    KhachHang *docKH = calloc(1, sizeof *docKH);
    if (DocFile("Test.bin", &docKH) == -1) {
        printf("Loi doc file");
        return 0;
    }

    printf("Ma so khach hang thu nhat la: %d\n", docKH[0].ma_khach_hang);
    printf("Ten khach hang thu 2 la: %s\n", docKH[1].ten);

    free(kh);
    free(docKH);
    getch();
    return 0;
}
