#include <stdio.h>
#include <math.h>
#include <string.h>
#include "Utils.h"

char *Den19[] = {
    "khong", "mot", "hai", "ba", "bon", "nam", "sau", "bay", "tam", "chin",
    "muoi", "muoi mot", "muoi hai", "muoi ba", "muoi bon", "muoi lam", "muoi sau",
    "muoi bay", "muoi tam", "muoi chin"
};

char *HangChuc[] = {"hai muoi", "ba muoi", "bon muoi", "nam muoi", "sau muoi", "bay muoi", "tam muoi", "chin muoi"};
char *NghinTroDi[] = {"", "nghin", "trieu", "ty", "nghin ty", "trieu ty"};


void bienDoiHangTram(int tien, char *result) {
    if (tien < 20) {
        strncat(result, Den19[tien], 10);
        return;
    }

    for (int i = 0; i < 8; i++) {
        char *hang_chuc = HangChuc[i];
        int val = 20 + 10 * i;
        if (val + 10 > tien) {
            if ((tien % 10) != 0) {
                strncat(result, hang_chuc, 10);
                strncat(result, " ", 3);
                strncat(result, Den19[tien % 10], 10);
                return;
            }
            strncat(result, hang_chuc, 10);
            return;
        }
    }
}

void bienDoiHangNghin(int tien, char *result) {
    int rem = tien / 100;
    int mod = tien % 100;
    if (rem > 0) {
        strncat(result, Den19[rem], 10);
        strncat(result, " ", 3);
        strncat(result, "tram", 6);
        if (mod > 0) {
            strncat(result, " ", 3);
        }
    }

    if (mod > 0) {
        bienDoiHangTram(mod, result);
    }
}

void BienDoiTienThanhChu(int tien, char *result) {
    if (tien < 100) {
        bienDoiHangTram(tien, result);
        return;
    }

    if (tien < 1000) {
        bienDoiHangNghin(tien, result);
        return;
    }

    for (int i = 1; i < 5; i++) {
        int didx = i - 1;
        int dval = pow(1000, i);
        if (dval > tien) {
            int mod = pow(1000, didx);
            int l = tien / mod;
            int r = tien - (l * mod);

            bienDoiHangNghin(l, result);
            strncat(result, " ", 3);
            strncat(result, NghinTroDi[didx], 100);

            if (r > 0) {
                strncat(result, " ", 4);
                BienDoiTienThanhChu(r, result);
            }

            return;
        }
    }
}


int NhapSo(int *n) {
    char nums[MAXSTR];

    fgets(nums, MAXSTR, stdin);
    if (sscanf(nums,"%d", n) != 1) {
        printf("Loi nhap khong thanh cong");
        return -1;
    }

    return 0;
}

float NhapThapPhan(float *n) {
    char nums[MAXSTR];

    fgets(nums, MAXSTR, stdin);
    if (sscanf(nums,"%f", n) != 1) {
        printf("Loi nhap khong thanh cong");
        return -1;
    }

    return 0;
}
