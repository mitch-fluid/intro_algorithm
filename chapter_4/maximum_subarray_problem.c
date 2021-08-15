#include <stdio.h>
#include <limits.h>

/* global data and result structure */
struct tuple {
    int l;
    int r;
    int max_sum;
};

/* test data from figure 4.3 */
int A[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
int n = (int) sizeof(A) / sizeof(int);

/* driver functions */
void exercise_4_1_1();
void exercise_4_1_2();
void exercise_4_1_5();

/* algorithm functions */
struct tuple find_max_subarray_brute_force(int *A, int n);
struct tuple find_max_crossing_subarray(int *A, int n, int low, int mid, int high);
struct tuple find_max_subarray(int *A, int n, int low, int high);
struct tuple find_max_subarray_kadane(int *A, int n);

/* helper functions */
void print_result(struct tuple result);

/* main driver */
int main(void) {

    int low = 0;
    int high = n - 1;
    int mid = low + ((high - low) >> 1);
    struct tuple result;

    printf("Divide and Conquer Algorithm of Maximum Subarray Problem\n");
    result = find_max_subarray(A, n, 0, n - 1);
    print_result(result);

    printf("Exercises: \n");
    exercise_4_1_1();
    exercise_4_1_2();
    exercise_4_1_5();
    return 0;
}

/********************************************************************************
 * For all negative input, FIND-MAXIMUM-SUBARRAY return the least loss if you 
 * still want to trade.
********************************************************************************/
void exercise_4_1_1() {
    int A[] = {-5, -3, -2, -1};
    int n = (int) sizeof(A) / sizeof(int);
    struct tuple result;
    printf("Exercise 4.1-1\n");
    result = find_max_subarray(A, n, 0, n - 1);
    print_result(result);
}

void exercise_4_1_2() {
    struct tuple result;

    printf("Exercise 4.1-2\n");
    printf("Brute-force method of solving the maximum-subarray problem:\n");
    result = find_max_subarray_brute_force(A, n);
    print_result(result);
}

void exercise_4_1_5() {
    struct tuple result;

    printf("Exercise 4.1-5\n");
    printf("Kadane algorithm of the maximum-subarray problem:\n");
    result = find_max_subarray_kadane(A, n);
    print_result(result);
}

/********************************************************************************
 * Given an nonempty A, find the nonempty, contiguous subarray of A whose values
 * have the largest sum.
 * Input  : A[n] n > 0
 * Output : l, r and max_sum
 * Algorithm:
 *  1.  max_sum = -infty, l = -1, r = -1
 *  2.  for i = 0 to n - 1
 *  3.      sum = 0
 *  4.      for j = i to n - 1
 *  5.          sum = sum + A[j];
 *  6.      if sum > max_sum
 *  7.          max_sum = sum
 *  8.          l = i
 *  9.          r = j
 * 10.  return l, r and max_sum    
********************************************************************************/
struct tuple find_max_subarray_brute_force(int *A, int n) {
    int max_sum = INT_MIN;
    int l = -1;
    int r = -1;
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = i; j < n; j++) {
            sum = sum + A[j];
            if (sum > max_sum) {
                max_sum = sum;
                l = i;
                r = j;
            }
        }
    }

    struct tuple result;
    result.l = l;
    result.r = r;
    result.max_sum = max_sum;

    return result;
}

/* page 71 */
struct tuple find_max_crossing_subarray(int *A, int n, int low, int mid, int high) {
    int sum; 
    int max_left, max_right;
    int left_sum, right_sum;

    /* find the max_left and left_sum */
    left_sum = INT_MIN;
    sum = 0;
    for (int i = mid; i >= low; i--) {
        sum += A[i];
        if (sum > left_sum) {
            left_sum = sum;
            max_left = i;
        }
    }

    /* find the max_right and right_sum */
    right_sum = INT_MIN;
    sum = 0;
    for (int j = mid + 1; j <= high; j++) {
        sum += A[j];
        if (sum > right_sum) {
            right_sum = sum;
            max_right = j;
        }
    }

    struct tuple result;
    result.l = max_left;
    result.r = max_right;
    result.max_sum = left_sum + right_sum;

    return result;
}

/* page 72 */
struct tuple find_max_subarray(int *A, int n, int low, int high) {
    struct tuple result;
    if (high == low) {
        result.l = low;
        result.r = high;
        result.max_sum = A[low];
        return result;
    }
    else {
        int mid = low + ((high - low) >> 1);
        struct tuple left = find_max_subarray(A, n, low, mid);
        struct tuple right = find_max_subarray(A, n, mid + 1, high);
        struct tuple cross = find_max_crossing_subarray(A, n, low, mid, high);

        int left_sum = left.max_sum;
        int right_sum = right.max_sum;
        int cross_sum = cross.max_sum;
        if (left_sum >= right_sum && left_sum >= cross_sum) return left;
        else if (right_sum >= left_sum && right_sum >= cross_sum) return right;
        else return cross;
    }
}

/********************************************************************************
 * Kadane's algorithm
 * Some definition:
 * MSA(j)  : Maximum Subarray of A[0..j]
 * LMSA(j) : Subarray of form A[i..j] with the maximum sum (0 <= i <= j)
 *           LMSA(j)   if LMSA(j).sum > MSA(j-1).sum
 * MSA(j) = 
 *           MSA(j-1)  other wise
 * It is also possible to update LMSA(j) from LMSA(j-1) which is a naive example
 * of dynamic programming. Since all subarrays of pattern A[i..j] can be 
 * constructed as A[i..j-1,j] or A[j]. Sum of A[i..j-1,j] follow the order of 
 * A[i..j-1] so only LMSA(j-1) should be considered.
 *            {A[j]} if LMSA(j-1).sum + A[j] < A[j]
 * LMSA(j) = 
 *            {LMSA(j-1), A[j]}
 *    j =  0  1   2  3   4  5  6   7  8
 * We use the beginning index i of LMSA(j) and the sum of LMSA(j) to track
 * Demo: {-2, 1, -3, 4, -1, 2, 1, -5, 4}
 * j = 0
 *     LMSA(0) = A[0..0] = {-2}
 *     i = 0
 *     MSA(0) = LMSA(0) = {-2} (LMSA(0).sum = -2 > MSA(-1).sum = -\infty)
 * j = 1
 *     LMSA(1) = A[1..1] = {1}
 *     i = 1
 *     MSA(1) = LMSA(1) = {1} (LMSA(1).sum = 1 > MSA(0).sum = -2)
 * j = 2
 *     LMSA(2) = A[1..2] = {1,-3} 
 *     i = 1
 *     MSA(2) = MSA(1) = {1} (LMSA(2).sum = -2 <= MSA(1).sum = 1)
 * j = 3
 *     LMSA(3) = A[3..3] = {4}
 *     i = 3
 *     MSA(3) = LMSA(3) = {4} (LMSA(3).sum = 4 > MSA(2).sum = 1)
 * j = 4
 *     LMSA(4) = A[3..4] = {4, -1}
 *     i = 3
 *     MSA(4) = MSA(3) = {4} (LMSA(4).sum = 3 <= MSA(3).sum = 4)
 * j = 5
 *     LMSA(5) = A[3..5] = {4, -1, 2} 
 *     i = 3
 *     MSA(5) = LMSA(5) = {4, -1, 2} (LMSA(5).sum = 5 > MSA(4).sum = 4)
 * j = 6
 *     LMSA(6) = A[3..6] = {4, -1, 2, 1}
 *     i = 3
 *     MSA(6) = LMSA(6) = {4, -1, 2, 1} (LMSA(6).sum = 6 > MSA(5).sum = 5)
 * j = 7
 *     LMSA(7) = A[3..7] = {4, -1, 2, 1, -5}
 *     i = 3
 *     MSA(7) = MSA(6) = {4, -1, 2, 1} (LMSA(7).sum = 1 <= MSA(6).sum = 6)
 * j = 8
 *     LMSA(8) = A[8..8] = {4}
 *     i = 8
 *     MSA(8) = MSA(7) = {4, -1, 2, 1} (LMSA(8).sum = 4 <= MSA(7).sum = 6)
 *    
********************************************************************************/
struct tuple find_max_subarray_kadane(int *A, int n) {
    int max_sum = INT_MIN;
    int l = -1;
    int r = -1;
    int local_max_sum = 0;
    int i = 0;

    for (int j = 0; j < n; j++) {
        /* obtain the LMSA(j) from LMSA(j-1) */
        if (local_max_sum < 0) {
            local_max_sum = A[j];
            i = j;
        }
        else local_max_sum += A[j];

        /* update the global solution if necessary */
        if (local_max_sum > max_sum) {
            max_sum = local_max_sum;
            l = i;
            r = j;
        }
    }

    struct tuple result;
    result.l = l;
    result.r = r;
    result.max_sum = max_sum;

    return result;
}

void print_result(struct tuple result) {
    printf("The maximum subarray is A[%d..%d] whose sum is %d\n", 
    result.l, result.r, result.max_sum);
}


