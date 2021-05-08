#include <assert.h>
#include <err.h>   
#include <math.h>  
#include <stdio.h> 
#include <stdlib.h>
                   
int compare_longs(const void *a, const void *b) {
    int x = *(int *)a;
    int y = *(int *)b;
    if (x < y)
        return -1;
    else if (x > y)
        return 1;
    return 0;
}

void sort(int *a, size_t n) {
    qsort(a, n, sizeof(int), compare_longs);
}

size_t med_index(size_t i) {
    return (size_t)(floor(i/2));
}

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

size_t partition(int pivot, int *array, size_t n_elts) {
    // find the pivot
    size_t pos = -1;
    for (size_t i = 0; i < n_elts; ++i) {
        if (array[i] == pivot) {
            pos = i;
            break;
        }
    }
    assert(pos >= 0);
    swap(&array[pos], &array[n_elts-1]);
    // now pivot is at the end of the array

    size_t i = 0;
    for (size_t j = 0; j < n_elts; ++j) {
        if (array[j] < pivot) {
            swap(&array[j], &array[i]);
            ++i;
        }
    }
    swap(&array[i], &array[n_elts-1]);

    return i;
}

int kth_largest(size_t k, int *array, size_t n_elts) {
    size_t n_sublists = n_elts/5;
    int *medians = malloc(n_sublists * sizeof(int));
    if (medians == NULL) { err(1, NULL); }

    // sort sublists of 5 elements
    for (size_t i = 0; i < n_sublists; ++i) {
        size_t start = i*5;
        size_t left = n_elts - start < 5 ? n_elts - start : 5;
        sort(&array[start], left);
        if (left == 5)
            medians[i] = array[start + 3];
        else
            medians[i] = array[start + med_index(left)];
    }

    // determine pivot (possibly recursively)
    int pivot;
    if (n_sublists < 5)
        pivot = medians[med_index(n_sublists)];
    else
        pivot = kth_largest(med_index(n_sublists), medians, n_sublists);

    // partition
    size_t rank = partition(pivot, array, n_elts);
    if (k < rank)
        return kth_largest(k, array, rank-1);
    else if (k > rank)
        return kth_largest(rank - k, &array[rank+1], n_elts-(rank+1));
    // else k == rank
    return pivot;
}

int main(int argc, char **argv) {
    size_t k;
    size_t n_elts;
    scanf("%li", &k);
    scanf("%li", &n_elts);
    int *array = malloc(n_elts * sizeof(int));
    if (array == NULL) { err(1, NULL); }
    for (size_t i = 0; i < n_elts; ++i)
        scanf("%i", &array[i]);

    printf("%i\n", kth_largest(k, array, n_elts));
}