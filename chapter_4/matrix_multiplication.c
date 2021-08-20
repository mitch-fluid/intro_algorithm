#include <stdio.h>
#include <math.h>

/* helper functions */
void print_matrix(int *A, int n);
void matrix_multiply_matrix(int *A, int *B, int *C, int n);

int main(void) {
    const int n = 2;
    const int ntot = n * n; 
    int A[ntot] = {1, 3,
                   7, 5};                  
    int B[ntot] = {6, 8,
                   4, 2};
    int C[ntot];
    matrix_multiply_matrix(A, B, C, n);
    print_matrix(C, n);
    return 0;
}


void print_matrix(int *A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) 
            printf("%d ", *((A + i * n) + j));
        printf("\n");
    }
}

void matrix_multiply_matrix(int *A, int *B, int *C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int c = 0;
            for (int k = 0; k < n; k++) {
                c += *((A + i * n) + k) * *((B + k * n) + j);
            }
            *((C + i * n) + j) = c;
        }
    }
}