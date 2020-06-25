#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "KhachHang.h"

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

    if (LuuFileKhachHang(kh, n, "TestWrite.bin") == -1) {
        printf("Loi luu file");
        return -1;
    }

    KhachHang *docKH = calloc(1, sizeof *docKH);
    if (DocFileKhachHang("Test.bin", &docKH) == -1) {
        printf("Loi doc file\n");
        return -1;
    }

    printf("Ma so khach hang thu nhat la: %d\n", docKH[0].ma_khach_hang);
    printf("Ten khach hang thu 2 la: %s\n", docKH[1].ten);

    printf("Bo sung khach hang \n");
    KhachHang *bo_sung = calloc(2, sizeof *bo_sung);
    for (int i = 0; i < n; i++) {
        do{
            bo_sung[i] = NhapKhachHang();
            printf("So ma khach hang la: %d\n", bo_sung[i].ma_khach_hang);
            printf("\n");
        } while(bo_sung[i].ma_khach_hang == -1);
    }

    if (BoSungKhachHang(bo_sung, 2, "TestWrite.bin") == -1) {
        printf("Khong the bo sung duoc vao file\n");
        return -1;
    }

    printf("Xoa khach hang");

    if (XoaKhachHangKhoiFile(1, "TestWrite.bin") == -1) {
        printf("Loi khi xoa khach hang khoi file\n");
        return -1;
    }

    KhachHang khach_hang_moi;
    strcpy(khach_hang_moi.ten, "Day la ten sua chua");
    strcpy(khach_hang_moi.dia_chi, "day la dia chi sua chua");
    khach_hang_moi.ma_cong_to = 1;
    if (SuaChuaKhachHang(2, "TestWrite.bin", khach_hang_moi) == -1) {
        printf("Loi khi xoa khach hang khoi file\n");
        return -1;
    }

    free(bo_sung);
    free(kh);
    free(docKH);
    return 0;
}
