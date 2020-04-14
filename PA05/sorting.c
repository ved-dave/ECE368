#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sorting.h"

//quick sort functions
static void quicksort_recursion(long * arr, int lb, int ub);
static int partition(long * arr, int lb, int ub);

//merge sort functions
static void mergesort_recursion(long * arr, long * tempArr, int lb, int ub, bool sortUp);
static void merge(long * arr, long * tempArr, int lb, int ub, bool sortUp);


//quick sort
void Quick_Sort(long *Array, int Size)
{
    if (Array != NULL)
    {
        quicksort_recursion(Array, 0, Size-1);
    }
    return;
}
// recursive quicksort function
static void quicksort_recursion(long * arr, int lb, int ub)
{
  while (ub > lb)
  {
    int ind = partition(arr, lb, ub);
    if (ind < (ub + lb) / 2)
    {
      quicksort_recursion(arr, ind + 1, ub);
      ub = ind - 1;
    }
    else
    {
      quicksort_recursion(arr, lb, ind - 1);
      lb = ind + 1;
    }
  }
}
// partition array with upper and lower indexes for quicksort
static int partition(long * arr, int lb, int ub)
{
    int ind = (rand() % (ub - lb + 1)) + lb; // random pivot makes lowest chance fr o(n^2) runtime
    int indDn = lb;
    int indUp = ub;

    long pivot = arr[ind];
    arr[ind] = arr[lb];
    arr[lb] = pivot;
    long tmp;
    
    while (indDn < indUp)
    {
        while (arr[indUp] > pivot)
        {
            indUp -= 1;
        }
        while (arr[indDn] <= pivot && indDn < ub)
        {
            indDn += 1;
        }
        if (indDn < indUp)
        {
            tmp = arr[indUp];
            arr[indUp] = arr[indDn];
            arr[indDn] = tmp;
        }
    }
    arr[lb] = arr[indUp];
    arr[indUp] = pivot;

    return indUp;
}

//merge sort
void Merge_Sort(long *Array, int Size)
{
    if (Array != NULL)
    {
        int memsize = sizeof(long) * Size;
        long * tempArr = malloc(memsize);

        memcpy(tempArr, Array, memsize);
        mergesort_recursion(Array, tempArr, 0, Size - 1, true);
        free(tempArr);
    }
    return;
}
// recursive function for merge sort
static void mergesort_recursion(long * arr, long * tempArr, int lb, int ub, bool sortUp)
{
    if (lb < ub)
    {
        int mid = (lb + ub) / 2;
        mergesort_recursion(tempArr, arr, lb, mid, true);
        mergesort_recursion(tempArr, arr, mid + 1, ub, false);
        merge(arr, tempArr, lb, ub, sortUp);
    }
}
// merge function
static void merge (long * arr, long * tempArr, int lb, int ub, bool mergeUp)
{
    int indUp = lb;
    int indDn = ub;

    if (mergeUp == true)
    {
        for (int i = lb; i <= ub; i++)
        {
            if (tempArr[indDn] >= tempArr[indUp])
            {
                arr[i] = tempArr[indUp++];
            }
            else
            {
                arr[i] = tempArr[indDn--];
            }
        }
    }
    else
    {
        for (int i = ub; i >= lb; i--)
        {
            if (tempArr[indDn] >= tempArr[indUp])
            {
                arr[i] = tempArr[indUp++];
            }
            else
            {
                arr[i] = tempArr[indDn--];
            }
        }   
    }

    return;
}
