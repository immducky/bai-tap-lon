#ifndef KhachHang_H
#define KhachHang_H
#define MAXSTR 100

typedef struct {
    int ma_khach_hang;
    char ten[MAXSTR];
    char dia_chi[MAXSTR];
    int ma_cong_to;
} KhachHang;

KhachHang NhapKhachHang();
int LuuFile(KhachHang *kh, int n, char ten_file[]);
int DocFile(KhachHang **kh, int *n, char ten_file[]);

#endif /* end of include guard */
