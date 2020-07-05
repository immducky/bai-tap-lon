#include <stdio.h>
#include <stdlib.h>
#include "KhachHang/KhachHang.h"
#include "ChiSoDien/ChiSoDien.h"
#include "GiaDien/GiaDien.h"
#include "Utils/Utils.h"

int ThemVaoKhachHang() {
    int n;
    int ma_khach_hang = LayMaKhachHang();
    printf("Nhap vao so luong khach hang can bo sung: ");
    NhapSo(&n);

    for (int i = 0; i < n; i++) {
        printf("");
    }
}

int TinhTienDien(int ma_khach_hang, int thang) {
    int dien_nang_TT = TinhDienNangTieuThu("CSDIEN.bin", ma_khach_hang, thang);
    int vi_tri_gia_dien = (dien_nang_TT - 1) / 5;

    if (vi_tri_gia_dien > )
}
