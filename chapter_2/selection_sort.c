#include "misc.h"

#include <stdio.h>
#include <stdlib.h>

/* function prototypes */
void SelectionSort(int *data, int n);

int main(int argc, char const *argv[])
{   
    int data[] = {4, 0, 7, 6, 2, 3, 5, 1, 9, 8};
    int n = sizeof(data) / sizeof(data[0]);

    printf("Selection sort demo\n");
    printf("Before sort: \n");
    PrintArray(data, n);

    SelectionSort(data, n);
    printf("After sort: \n");
    PrintArray(data, n);
    
    return EXIT_SUCCESS;
}

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
