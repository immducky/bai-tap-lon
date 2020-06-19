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

/*
 * @detail Luu struct vao file voi do dai size
 * @return tra ve 0 neu khong co loi va -1 neu viec luu bi loi
 */
int LuuFile(KhachHang *kh, size_t size, char ten_file[]);

/*
 * @detail doc tu ten file roi viet vao heap khach hang da duoc malloc truoc
 * @return tra ve so luong bien struct ma no doc duoc, neu bi loi se tra ve -1
 */
int DocFile(char ten_file[], KhachHang **kh);

#endif /* end of include guard */
