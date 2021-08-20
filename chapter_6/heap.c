#include <stdio.h>
#include <stddef.h>
/** 
 * Basics of Heap (data structure)
 * 1. Definition: A heap is a nearly complete binary tree (Complete tree is
 * refered as a full tree in the text.)
 * 2. A heap can be represent in an array A[n], where A[1] is the root and for 
 * a node i 
 *      1. parent(i) = floor(i/2)
 *      2. left(i) = 2i
 *      3. right(i) = 2i + 1
 * 3. Max-heap property
 *      A[parent(i)] >= A[i]
 * 4. Min-heap property
 *      A[parent(i)] <= A[i]
 * 5. Height of a heap of only one node is 0
 * 6. For a heap, several procedures are available
 *      1. max_heapify O(lg(n))
 *      2. build_max_heap O(n)
 *      3. heapsort O(nlg(n))
 *      4. max_heap_insert, heap_extract_max, heap_increase_key and heap_maximum
 * Exercises
 * 6.1-1 
 *      Solution: For a full tree of height h, we have 2^{h+1} - 1 nodes. For a 
 *      minimum complete tree, we have 2^{h} - 1 + 1 = 2^{h} nodes
 * 6.1-2
 *      Solution: n-element heap is of height h. From ex 6.1-1, 
 *                 2^{h} <= n <= 2^{h+1} - 1 < 2^{h+1}
 *      so that lg(n) - 1 < h <= lg(n) i.e. h = floor(lg(n))
 * 6.1-3
 *      Solution: 
 *      Suppose the root of the subtree is at i. For any node in that subtree
 *      A[j] <= A[floor(j/2)] <= .. <= A[i]
 * 6.1-4
 *      Solution: The smallest element must reside in one of the leaf nodes. 
 *      Since any nodes of height h must be smaller than at least one node of 
 *      height h - 1 i.e. its parent. 
 * 6.1-5
 *      Solution: Yes since A[i] >= A[floor(lg(i))]
 * 6.1-6
 *      Solution: No. In tree view 
 *              23
 *         17        14
 *       6    13   10   1 
 *     5     7  12
*/

/* function prototypes */
/* Algorithms in text and their test drivers */
void max_heapify(int *A, size_t n, size_t heap_size, size_t i); 
void test_max_heapify(void);

/* helper functions */
void print_heap(int *A, size_t n, size_t heap_size);

int main(void) {
    /* text */
    test_max_heapify();
    return 0;
}

/* drivers */
void test_max_heapify(void) {
    /* A[1..n-1] represents a heap whose maximum size is n-1 */
    int A[] = {-1, 16, 4, 10, 14, 7, 9, 3, 2, 8, 1};
    size_t n = sizeof(A) / sizeof(int);
    size_t heap_size = n - 1;
    size_t i = 2;

    print_heap(A, n, heap_size);
    max_heapify(A, n, heap_size, i);
    print_heap(A, n, heap_size);
}

/* helper functions */
void print_heap(int *A, size_t n, size_t heap_size) {
    if (heap_size > n - 1) {
        printf("Illegal argument\n");
        return;
    }
    for (size_t i = 1; i <= heap_size; i++) printf(" %d ", A[i]);
    printf("\n");
}

/* text algorithms */
/********************************************************************************
 * MAX-HEAPIFY
 * Input: A, i
 * Output: A
 * Purpose: The left and right subtree of A[i] are max-heaps but A[i] might be 
 * smaller than its children i.e. violating the max-heap property. This 
 * algorithm fix this violation.
 * Algorithms:
 *      1.  l = LEFT(i)
 *      2.  r = RIGHT(i)
 *      3.  largest = i;
 *      4.  if l <= heap.size and A[l] > A[i]
 *      5.       largest = l
 *      6.  if r <= heap.size and A[r] > A[largest]
 *      7.       largest = r
 *      8.  if largest != i
 *      9.       exchange A[i] and A[largest]
 *     10.       MAX_HEAPIFY(A, largest)
********************************************************************************/
void max_heapify(int *A, size_t n, size_t heap_size, size_t i) {
    int l = 2 * i;
    int r = 2 * i + 1;
    int largest = i;
    if (l <= heap_size && A[l] > A[i]) largest = l;
    if (r <= heap_size && A[r] > A[largest]) largest = r;
    if (largest != i) {
        int swap = A[i];
        A[i] = A[largest];
        A[largest] = swap;
        max_heapify(A, n, heap_size, largest);
    }
}