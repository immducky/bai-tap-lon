#include <stdio.h>
#include "Utils.h"

int NhapSo(int *n) {
    char nums[MAXSTR];

    fgets(nums, MAXSTR, stdin);
    if (sscanf(nums,"%d", n) != 1) {
        printf("Loi nhap khong thanh cong");
        return -1;
    }

    return 0;
}
