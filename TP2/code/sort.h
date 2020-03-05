#ifndef SORT_H
#define SORT_H
// Sort function
int cmpfunc (const void * a, const void * b);
void insertionSort(unsigned long long arr[], int n);
void merge(long arr[], int l, int m, int r);
void mergeSort(long arr[], int l, int r);
#endif