#include "misc.h"
#include <stdio.h>

void PrintArray(int *data, int n) {
    for (int i = 0; i < n; i++)
    {
        printf("%d ", data[i]);
    }
    printf("\n");
}