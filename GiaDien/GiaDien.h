#ifndef GIADIEN_NEW_H
#define GIADIEN_NEW_H

enum Bac {Bac_1 = 0, Bac_2, Bac_3, Bac_4, Bac_5, Bac_6};

typedef struct {
    float don_gia[6];
    enum Bac bac;
} GiaDien;


int NhapGiaDien(GiaDien **dien_nang_TT);

int LuuFileGiaDien(GiaDien *dien_nang_TT, int n, char ten_file[]);
int DocFileGiaDien(char ten_file[], GiaDien **dien_nang_TT);

int BoSungGiaDien(GiaDien *dien_nang_TT, size_t n, char ten_file[]);
int XoaGiaDienKhoiFile(int dien_nang_TT, char ten_file[]);
int SuaChuaGiaDien(int ma_khach_hang, char ten_file[], GiaDien dien_nang_TT);

int TinhTienDien(char ten_file[], int dien_nang_TT);

#endif /* end of include guard */
