#include "misc.h"
#include "sort.h"

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[]) {
    int data[] = {4, 0, 7, 6, 2, 3, 5, 1, 9, 8};
    int n = sizeof(data) / sizeof(data[0]);

    printf("Merge sort demo\n");
    printf("Before sort: \n");
    PrintArray(data, n);

    MergeSort(data, 0, n - 1);
    printf("After sort: \n");
    PrintArray(data, n);

    return EXIT_SUCCESS;
}