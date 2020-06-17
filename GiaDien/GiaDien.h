#ifndef GIADIEN_NEW_H
#define GIADIEN_NEW_H

typedef struct {
    int so_dien_nang_tieu_thu;
    int don_gia;
} GiaDien;

GiaDien NhapGiaDien();
GiaDien BangGia();
int LuuFile(GiaDien *dien_nang_TT, int n, char ten_file[]);
int DocFile(char ten_file[], GiaDien **dien_nang_TT, int *n);

#endif /* end of include guard */
