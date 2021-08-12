#include "misc.h"

#include <stdio.h>
#include <stdlib.h>

/* function prototypes */
void MergeSort(int *data, int p, int r);
void Merge(int *data, int lo, int mid, int hi);

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

/**
 * Merge two sorted subarray into one sorted 
 * subarray. The index is inclusive 
 * L : p,...,q 
 * R : q+1,...,r
 */
void Merge(int *data, int p, int q, int r) {

    /* size of the local copy */
    int n_1 = q - p + 1;
    int n_2 = r - q;

    /* local copy */
    int L[n_1], R[n_2];

    /* copy */
    for (int i = 0; i < n_1; i++) {
        L[i] = data[p + i];
    }
    for (int j = 0; j < n_2; j++) {
        R[j] = data[q + 1 + j];
    }
    
    /**
     * index of subarray and merged array
     * i: L
     * j: R
     * k: data
     */
    int i = 0;
    int j = 0; 
    int k = p; 
    while (i < n_1 && j < n_2) {
        if (L[i] <= R[j]) {
            data[k] = L[i];
            i++;
        }
        else {
            data[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy remaining data in L if any */ 
    while (i < n_1) {
        data[k] = L[i];
        i++;
        k++;
    }

    /* Copy remaining data in R if any */
    while (j < n_2) {
        data[k] = R[j];
        j++;
        k++;
    }
}

/**
 * recursively sort the data 
 */
void MergeSort(int *data, int p, int r) {
    
    if (p < r) {
        int q = p + (r - p) / 2;
        MergeSort(data, p, q);
        MergeSort(data, q+1, r);
        Merge(data, p, q, r);
    }
}