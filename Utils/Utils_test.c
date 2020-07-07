#include <stdio.h>
#include <stdlib.h>
#include "Utils.h"

int main(void)
{
    int n;
    printf("Nhap vao mot so: ");
    NhapSo(&n);
    printf("So do la: %d\n", n);

    char *result = calloc(1000, sizeof *result);
    BienDoiTienThanhChu(n, result);
    printf("So do thanh chu la: %s\n", result);
    free(result);
    return 0;
}
