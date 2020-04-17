//main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell_array.h"
#include "shell_list.h"

int main (int argc, char *argv[]){
    if (argc != 4)
    {
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "-a") && strcmp(argv[1], "-l"))
    {
        return EXIT_FAILURE;
    }

    // array
    if (!(strcmp(argv[1], "-a")))
    {
        int size; 
        long *arr; 
        long n_comp = 0;

        //Array_Load_From_File(argv[2], &size);
        arr = Array_Load_From_File(argv[2], &size);
        Array_Shellsort(arr, size, &n_comp);
        int num = Array_Save_To_File(argv[3], arr, size);
        
        if (num!=size)
        {
            // printf("ERROR in fwrite");
            return EXIT_FAILURE;
        }
        free(arr);
    }
    // list
    else if (!(strcmp(argv[1], "-l")))
    {
        Node * head;
        long n_comp = 0;

        head = List_Load_From_File(argv[2]);
        head = List_Shellsort(head, &n_comp);
        List_Save_To_File(argv[3], head);
        
        //free memory
        while (head != NULL)
        {
            Node * toDelete = head->next;
            free(head);
            head = toDelete;
        }
    }
    else
    {
        // printf("error method of shell sort to use\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}