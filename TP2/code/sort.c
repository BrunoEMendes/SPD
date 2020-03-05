#include "sort.h"
#include "main.h"

int print_output =  0;
int time_output = 0;
int merge_sort = 0;
int i_sort = 0;
int q_sort = 0;

/**
* função de comparação do qSort
* void * a -> item a comparar
* void * b -> item a comparar
*/
int cmpfunc (const void * a, const void * b) {
    return ( *(unsigned long long  *)a - * (unsigned long long *)b );
}
//------------------------- isort ref: https://www.geeksforgeeks.org/insertion-sort/ --------------------------------------------------------
/* Function to sort an array using insertion sort*/
void insertionSort(unsigned long long arr[], int n)
{
    int i, j;
    unsigned long long key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
// ----------------------end of isort-------------------------------------------------------------------------------------------------------------
//---------------------- merge sort ref:https://www.geeksforgeeks.org/merge-sort/ ----------------------------------------------------------------
void merge(long arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    long L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(long arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

void sort_function(long * result, int size)
{
    if(merge_sort == 1)
        mergeSort(result, 0, size);
    if(i_sort == 1)
        insertionSort(result, size);
    if(q_sort == 1)
        qsort(result, size, sizeof(unsigned long long ),cmpfunc);
}

//----------------end merge sort----------------------------
