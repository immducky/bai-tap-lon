#include <stdio.h>
#include <stdlib.h>
#include "KhachHang.h"
#include "../Utils/Utils.h"

int MaKhachHang = 1;

KhachHang NhapKhachHang() {
    KhachHang kh;
    kh.ma_khach_hang = -1;

    printf("Nhap vao ten khach hang: ");
    fgets(kh.ten, 100, stdin);

    printf("Nhap vao dia chi khach hang: ");
    fgets(kh.dia_chi, 100, stdin);

    kh.ma_khach_hang = MaKhachHang;
    kh.ma_cong_to = MaKhachHang;
    MaKhachHang++;

    return kh;
}

int LuuFileKhachHang(KhachHang *kh, int n, char ten_file[]) {
    FILE *fp = fopen(ten_file, "wb");

    if (fwrite(&n, sizeof(int), 1, fp) != 1) {
        printf("Loi Nhap vao khac hang\n");
        fclose(fp);
        return -1;
    }

    if (fwrite(kh, sizeof(KhachHang), n, fp) != n) {
        printf("Loi Nhap vao khac hang\n");
        fclose(fp);
        return -1;
    }

    fclose(fp);
    return 0;
}

int DocFileKhachHang(char ten_file[], KhachHang **kh) {
    int n;
    FILE *file;

    file = fopen(ten_file, "rb");
    if (file == NULL) {
        perror("Khong mo duoc file: ");
        return -1;
    }

    if (fread(&n, sizeof(int), 1, file) != 1) {
        perror("Khong the doc duoc file: ");
        return -1;
    }

    KhachHang *temp = realloc(*kh, n * sizeof(KhachHang));
    if (temp != NULL) {
        *kh = temp;
    } else {
        perror("Loi khi goi ham realloc: ");
        free(*kh);
        exit(1);
    }
    if (fread(*kh, sizeof(KhachHang), n, file) != n) {
        perror("Khong doc duoc file: ");
        return -1;
    }

    fclose(file);
    return n;
}

int BoSungKhachHang(KhachHang *kh, int n, char ten_file[]) {
    KhachHang *KH_tu_file = calloc(0, sizeof(KhachHang));
    int size = DocFileKhachHang(ten_file, &KH_tu_file);
    if (size == -1) {
        printf("Khong doc duoc du lieu tu file\n");
        return -1;
    }

    KhachHang *temp = realloc(KH_tu_file, (size + n) * sizeof(KhachHang));
    if (temp != NULL) {
        KH_tu_file = temp;
    } else {
        perror("Loi khi goi ham realloc: ");
        free(KH_tu_file);
        exit(1);
    }

    for (int i = size; i < (size + n); i++) {
        KH_tu_file[i] = kh[i - size];
    }
    size += n;
    if (LuuFileKhachHang(KH_tu_file, size, ten_file) == -1) {
        printf("Loi khong luu duoc vao file\n");
        return -1;
    }

    free(KH_tu_file);;
    return 0;
}

int TimViTriKhachHang(KhachHang *kh, int size, int ma_khach_hang) {
    int mid;
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        mid = left + (right - left) / 2;

        if (kh[mid].ma_khach_hang == ma_khach_hang) {
            return mid;
        }

        if (kh[mid].ma_khach_hang < ma_khach_hang) {
            left = mid + 1;
            continue;
        }

        right = mid - 1;
    }

    return -1;
}

int XoaKhachHangKhoiFile(int ma_khach_hang, char ten_file[]) {
    int pos = 0;
    KhachHang *kh = calloc(0, sizeof(KhachHang));
    int size = DocFileKhachHang(ten_file, &kh);
    if (size == -1) {
        printf("Loi khi doc file\n");
        free(kh);
        return -1;
    }

    pos = TimViTriKhachHang(kh, size, ma_khach_hang);
    printf("vi tri la: %d\n", pos);
    if (pos == -1) {
        printf("Khong tim thay khach hang\n");
        return -1;
    }

    for (int i = pos; i < size-1; i++) {
        kh[i] = kh[i+1];
    }
    size--;

    if (LuuFileKhachHang(kh, size, ten_file) == -1) {
        printf("Khong Luu vao file duoc\n");
        free(kh);
        return -1;
    }

    free(kh);
    return 0;
}

int SuaChuaKhachHang(int ma_khach_hang, char ten_file[] ,KhachHang kh) {
    int pos;
    kh.ma_khach_hang = ma_khach_hang;
    KhachHang *file_khach_hang = (KhachHang*)calloc(0, sizeof(KhachHang));
    int size = DocFileKhachHang(ten_file, &file_khach_hang);
    if (size == -1) {
        printf("Loi doc file\n");
        free(file_khach_hang);
        return -1;
    }

    if (ma_khach_hang > size || ma_khach_hang <= 0) {
        printf("Vi tri khong ton tai\n");
        free(file_khach_hang);
        return -1;
    }

    pos = TimViTriKhachHang(file_khach_hang, size, ma_khach_hang);
    if (pos == -1) {
        printf("Khong tim thay  khach hang");
        return -1;
    }

    file_khach_hang[pos] = kh;

    if (LuuFileKhachHang(file_khach_hang, size, ten_file) == -1) {
        printf("Khong Luu vao file duoc\n");
        free(file_khach_hang);
        return -1;
    }

    free(file_khach_hang);
    return 0;
}

int TimKhachHang(char ten_file[], int ma_khach_hang, KhachHang *kh) {
    int pos;
    KhachHang *file_khach_hang = (KhachHang*)calloc(0, sizeof(KhachHang));

    int size = DocFileKhachHang(ten_file, &file_khach_hang);
    if (size == -1) {
        printf("Loi doc file\n");
        free(file_khach_hang);
        return -1;
    }

    if (ma_khach_hang > size || ma_khach_hang <= 0) {
        printf("Vi tri khong ton tai\n");
        free(file_khach_hang);
        return -1;
    }

    pos = TimViTriKhachHang(file_khach_hang, size, ma_khach_hang);
    if (pos == -1) {
        printf("Khong tim thay  khach hang");
        free(file_khach_hang);
        return -1;
    }

    *kh = file_khach_hang[pos];
    free(file_khach_hang);
    return 0;
}

void DatMaKhachHang(int n) {
    MaKhachHang = n;
}
