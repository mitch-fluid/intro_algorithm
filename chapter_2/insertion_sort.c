#include "misc.h"

#include <stdio.h>
#include <stdlib.h>

/* function prototypes */
void InsertionSort(int *data, int n);
void ReverseInsertionSort(int *data, int n);

int main(int argc, char const *argv[]) {   
    int data[] = {4, 0, 7, 6, 2, 3, 5, 1, 9, 8};
    int n = sizeof(data) / sizeof(data[0]);

    printf("Insertion sort demo\n");
    printf("Before sort: \n");
    PrintArray(data, n);

    InsertionSort(data, 10);
    printf("After sort: \n");
    PrintArray(data, n);

    ReverseInsertionSort(data, n);
    printf("After reverse sort: \n");
    PrintArray(data, n);

    return EXIT_SUCCESS;
}

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

void ReverseInsertionSort(int *data, int n) {
    for (int i = 1; i < n; i++) {
        int key = data[i];
        int j = i - 1; 
        while(j >= 0 && data[j] < key) {
            data[j+1] = data[j];
            j--;
        }
        data[j+1] = key;
    }
}