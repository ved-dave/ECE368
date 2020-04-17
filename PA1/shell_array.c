//shell_array
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <stdbool.h>
#include <values.h>
#include "shell_array.h"

long *Array_Load_From_File(char * filename, int * size)
{
    FILE * fptr = fopen(filename, "rb");
    if (fptr == NULL)
    {
        return NULL;
    }
    long temp; //temp
    int count = 0;
    while (!feof(fptr))
    {
        fread(&temp, sizeof(long), 1, fptr);
        count++;
    }
    count--; //size of the array
    *size = count;

    fseek(fptr, 0, SEEK_SET);
    long *array = malloc(sizeof(long) * (count));
    if (array == NULL)
    {
        printf("malloc fail\n");
    }
    for (int i = 0; i < count; i ++)
    {
        fread(&array[i], sizeof(long), 1, fptr);
    }

    fclose(fptr);
    return array;
}
int Array_Save_To_File(char * filename, long * array, int size)
{
    FILE * fptr = fopen(filename, "wb");
    if (fptr == NULL){
        printf("error1");
        return 0;
    }
    int num;
    num = fwrite(array, sizeof(long), size, fptr);
    if (size!=num){
        printf("ERROR: write file error\n");
    }
    
    //free memory
    fclose(fptr);
    return num;
}

void Array_Shellsort(long *array, int size, long *n_comp)
{
    if (!size)
    {
      array = NULL;
      printf("error2\n");
      return;
    }
    int k = 0; // k value
    int a = 0; // placeholder
    long tmp; // temp value

    // counters
    int i;
    int j;

    // find max K
    while(true)
    {
        a = (a * 3) + 1;
        if (a > size)
            break;
        else
            k = a;
        // printf("k = %d\n", k);
    }
    
    // shell sort - iterate down through array of k values adn do insertion sort

    while(k >= 1)
    {
        for(i = k; i < size; i++)
        {
            tmp = array[i];
            j = i;
            (* n_comp)++;
            while(j >= k && array[j - k] > tmp)
            {
                array[j] = array[j - k];
                j = j - k;
            }
            array[j] = tmp;
        }
        k = (k - 1) / 3;
    }

    /*printf("SORTED\n");
    for (i = 0; i < size; i++)
    {
        printf("%ld ", array[i]);
        printf("\n");
    } */
    return;
}