#include "sort.h"

/* some private functions */
void Merge(int *data, int p, int q, int r);

/**
 * Collection of sort algorithms for integers. 
 * Time complexity in the worst case is shown
 * by \Theta notation. All logrithm is of base
 * 2.
*/

/**
 * Selection sort
 * \Theta (n^2)
*/

void SelectionSort(int *data, int n) {
    for (int i = 0; i < n; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (data[j] < data[min]) {
                min = j; 
            }
        }
        /* swap i with the min */
        int swap = data[i];
        data[i] = data[min];
        data[min] = swap;
    }
}

/**
 * Insertion sort
 * \Theta (n^2)
*/

void InsertionSort(int *data, int n) {
    for (int i = 1; i < n; i++) {
        int key = data[i];
        int j = i - 1;
        while (j >= 0 && data[j] > key) {
            data[j+1] = data[j];
            j--;
        }
        data[j+1] = key;
    }
}

/**
 * Bubble sort
 * \Theta (n^2)
*/

void BubbleSort(int *data, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = n - 1; j > i; j--) {
            if (data[j] < data[j-1]) {
                int swap = data[j];
                data[j] = data[j-1];
                data[j-1] = swap;
            }
        }
    }
}

/**
 * Merge sort
 * \Theta (n\log(n))
*/

void MergeSort(int *data, int p, int r) {
    
    if (p < r) {
        int q = p + (r - p) / 2;
        MergeSort(data, p, q);
        MergeSort(data, q+1, r);
        Merge(data, p, q, r);
    }
}

/**
 * Merge sub-arrays L and R into one sorted
 * array. All index is inclusive
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

