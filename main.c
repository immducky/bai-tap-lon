#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "KhachHang/KhachHang.h"
#include "ChiSoDien/ChiSoDien.h"
#include "GiaDien/GiaDien.h"
#include "Utils/Utils.h"


int LuuHoaDon(int ma_khach_hang) {
    FILE *hoa_don = fopen("./HOADON.txt", "a");
    if (hoa_don == NULL) {
        printf("khong doc duoc file hoa don\n");
        return -1;
    }

    int thang_thu_phi = TimKyThuPhi(ma_khach_hang, "./CSDIEN.bin");
    int dien_nang_TT = TinhDienNangTieuThu("./CSDIEN.bin", ma_khach_hang, thang_thu_phi);
    int tien_dien = TinhTienDien("./GIADIEN.bin", dien_nang_TT);
    fprintf(hoa_don, "%d \t %d \t %d \t %d\n", ma_khach_hang, thang_thu_phi, dien_nang_TT, tien_dien);

    fclose(hoa_don);
    return 0;
}

int InRaHoaDon(int ma_khach_hang) {
    KhachHang kh;
    ChiSoDien chi_so;
    bool flag;
    int MKH, thang_thu_phi, dien_nang_TT, tien_dien;
    char str[100];
    char *result = calloc(1000, sizeof *result);

    FILE *file_hoa_don = fopen("./HOADON.txt", "r");
    if (file_hoa_don == NULL) {
        printf("Khong mo duoc file hoa don\n");
        return -1;
    }

    while (fgets(str, 100, stdin) != NULL) {
        sscanf(str, "%d %d %d %d", &MKH, &thang_thu_phi, &dien_nang_TT, &tien_dien);
        if (MKH == ma_khach_hang) {
            flag = true;
            break;
        }
    }

    if (flag != true) {
        printf("Khong tim thay ma khach hang trong file hoa don");
        return -1;
    }

    if(TimKhachHang("./KH.bin", MKH, &kh) == -1) {
        printf("Khong tim thay ma khach hang");
        return -1;
    }
    if(TimChiSoDien("./CSDIEN.bin", MKH, &chi_so) == -1) {
        printf("Khong tim thay ma khach hang");
        return -1;
    }

    printf("Hoa don tien dien cua khach hang la: ");
    printf("Ma khach hang: %d\n", MKH);
    printf("Ten khach hang: %s\n", kh.ten);
    printf("Dia chi khach hang: %s\n", kh.dia_chi);
    printf("Ma cong to: %d\n", kh.ma_khach_hang);
    printf("Ky thu phi: thang %d\n", chi_so.ky_thu_phi + 1);
    if (chi_so.ky_thu_phi == 1) {
        printf("Tu ngay: 0");
    } else {
        printf("Tu ngay: %d\n", chi_so.ngay_chot_chi_so[chi_so.ky_thu_phi-1]);
    }
    printf("Den ngay: %d\n", chi_so.ngay_chot_chi_so[chi_so.ky_thu_phi]);
    printf("Dien nang tieu thu: %d\n", dien_nang_TT);
    printf("Tien dien la: %d\n", tien_dien);
    printf("Thue 10%: %d\n", tien_dien / 10);
    printf("Tong cong tien hang: %d\n", tien_dien + tien_dien / 10);

    BienDoiTienThanhChu(tien_dien + tien_dien / 10, result);
    printf("So tien viet bang chu: %s\n", result);

    fclose(file_hoa_don);
    free(result);
    return 0;
}

int nhapKH() {
    int n;
    printf("Nhap vao so luong khach hang: ");
    NhapSo(&n);
    KhachHang *kh = calloc(n, sizeof(KhachHang));
    ChiSoDien *chi_so = calloc(n, sizeof(ChiSoDien));
    for (int i = 0; i < n; i++) {
        do{
            kh[i] = NhapKhachHang();
            printf("So ma khach hang la: %d\n", kh[i].ma_khach_hang);
            printf("\n");

            printf("Nhap vao chi so dien cua khach hang %d\n", i+1);
            chi_so[i] = NhapChiSoDien(i+1);
            printf("\n");

        } while(kh[i].ma_khach_hang == -1);
    }

    if (LuuFileKhachHang(kh, n, "./KH.bin") == -1) {
        printf("Loi luu file\n");
        return -1;
    }

    if (LuuFileChiSoDien(chi_so, n, "./CSDIEN.bin") == -1) {
        printf("Loi luu file\n");
        return -1;
    }

    free(kh);
    free(chi_so);
    return 0;
}

void chinhSuaFileKhachHang(int choice) {
    int n;
    int ma_khach_hang;
    KhachHang kh_moi;
    KhachHang *kh;
    ChiSoDien *chi_so;
    switch (choice) {
        case 1:
            printf("nhap vao ma khach hang: ");
            NhapSo(&ma_khach_hang);

            printf("Nhap vao ten moi: ");
            fgets(kh_moi.ten, 100, stdin);
            printf("Nhap vao dia chi moi: ");
            fgets(kh_moi.dia_chi, 100, stdin);
            printf("Nhap vao ma cong to moi: ");
            NhapSo(&kh_moi.ma_cong_to);

            SuaChuaKhachHang(ma_khach_hang, "./KH.bin", kh_moi);
            break;
        case 2:
            printf("nhap vao ma khach hang: ");
            NhapSo(&ma_khach_hang);

            if (XoaKhachHangKhoiFile(ma_khach_hang, "./KH.bin") == -1) {
                printf("Xoa that bai");
                break;
            }
            printf("Xoa thanh cong");
            break;
        case 3:
            printf("Nhap vao so luong can them vao: ");
            NhapSo(&n);

            kh = calloc(n, sizeof(KhachHang));
            chi_so = calloc(n, sizeof(ChiSoDien));
            for (int i = 0; i < n; i++) {
                do{
                    kh[i] = NhapKhachHang();
                    printf("So ma khach hang la: %d\n", kh[i].ma_khach_hang);
                    printf("\n");

                    printf("Nhap vao chi so dien cua khach hang %d\n", i+1);
                    chi_so[i] = NhapChiSoDien(i+1);
                    printf("\n");

                } while(kh[i].ma_khach_hang == -1);
            }

            BoSungKhachHang(kh, n, "./KH.bin");
            BoSungChiSoDien(chi_so, n, "./CSDIEN.bin");
            free(kh);
            free(chi_so);
            break;
        default:
            printf("Khong co lua chon do");
    }
}

void hienThiMenu(int choice) {
    GiaDien *gia_dien = calloc(6, sizeof *gia_dien);
    int choice2;
    int ma_khach_hang;
    switch (choice) {
        case 1:
            while (nhapKH() == -1) {
                printf("Nhap khach hang sai xin hay nhap lai\n");
            }
            break;
        case 2:
            while (true) {
                printf("1. Sua chua file khach hang");
                printf("2. Xoa khach hang");
                printf("3. Them vao khach hang");
                printf("Lua chon cua ban: ");
                if (NhapSo(&choice2) != -1) {
                    printf("Lua chon sai");
                    continue;
                }
                chinhSuaFileKhachHang(choice2);
                break;
            }
            break;
        case 3:
            printf("Nhap vao ma so khach hang: ");
            while(NhapSo(&ma_khach_hang) == -1) {
                printf("Nhap sai xin hay nhap lai\n");
            }
            LuuHoaDon(ma_khach_hang);
            break;
        case 4:
            printf("Nhap vao ma so khach hang: ");
            while(NhapSo(&ma_khach_hang) == -1) {
                printf("Nhap sai so xin hay nhap lai\n");
            }
            InRaHoaDon(ma_khach_hang);
            break;
        case 5:
            while (NhapGiaDien(&gia_dien) == -1) {
                printf("Nhap sai gia dien xin nhap lai\n");
            }
            LuuFileGiaDien(gia_dien, 6, "GIADIEN.bin");
            break;
        case 6:
            while(true) {
                printf("1. Sua chua file khach hang");
                printf("2. Xoa khach hang");
                printf("3. Them vao khach hang");
                printf("Lua chon cua ban: ");
                if (NhapSo(&choice2) != -1) {
                    printf("Lua chon sai");
                }
                chinhSuaFileKhachHang(choice2);
                break;
            }
            break;
        case 7:
            break;
        default:
            printf("Khong co lua chon do");

    free(gia_dien);
    }
}

int main()
{
    int choice = 0;
    while(choice != 7) {
        printf("1. Nhap vao khach hang moi\n");
        printf("2. Sua chua, xoa, them vao khach hang\n");
        printf("3. Tinh tien dien cua khach hang\n");
        printf("4. In ra hoa don dien\n");
        printf("5. Nhap vao gia dien moi\n");
        printf("6. Sua chua, xoa, bo sung gia dien\n");
        printf("7. thoat\n");
        printf("Lua chon cua ban: ");
        if (NhapSo(&choice) == -1) {
            printf("Lua chon sai xin hay chon lai\n");
            printf("\n\n\n");
            continue;
        }
        hienThiMenu(choice);
    }
    return 0;
}
