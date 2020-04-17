#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <values.h>
#include <stdbool.h>
#include "shell_list.h"

typedef struct List {
    Node *node;
    struct List *next;
} List;

// static void testList(Node* head);
static void freeSubList(List * subList);
static List * addList(Node * sublist);
static Node * addNode(long value);
static List * createSublists(List * listHead, int k, long * n_comp, bool sortUp);
static void addAndSort(Node ** head, Node * ins, long *n_comp, bool sortUp);
static Node * removeNode(Node ** head);

// create unsorted list
Node *List_Load_From_File(char *filename)
{
    FILE * fptr = fopen(filename, "rb");
    if (fptr == NULL)
    {
        return NULL;
    }
    long temp; //temp
    Node * head;
    Node * tmp = NULL; // temp/helper node
    //int count = 0;
    while (feof(fptr) == 0)
    {
        fread(&temp, sizeof(long), 1, fptr);
        head = addNode(temp);
	    head -> next = tmp;
	    tmp = head;
    }
    Node * extra = head;
    head = extra->next; // delete extra node
    free(extra);

    //testList(head);
    fclose(fptr);
    return head;
}

// add new node
static Node * addNode(long value)
{
    Node * new = malloc (sizeof (Node));
    new -> value = value;
    new -> next = NULL;
    return new;
}
// add new list
static List * addList(Node * sublist)
{
    List * new = malloc(sizeof(List));
    new -> node = sublist;
    new -> next = NULL;
    return new;
} 

// save list to file
int List_Save_To_File(char *filename, Node *list)
{
    FILE * fptr = fopen(filename, "wb");
    if (fptr == NULL)
    {
        return 0;
    }
    Node * print = list;
    int num = 0;
    while (print != NULL)
    {
        fwrite(&print->value, sizeof(long), 1, fptr);
        print = print->next;
        num++;
    }
    fclose(fptr);
    return num;
}
// shell sort
Node *List_Shellsort(Node *list, long *n_comp)
{
    if (list==NULL)
    {
        return NULL;
    }
    int size = 0;
    int a = 0;
    int k = 0;

    Node * count = list;
    // calculate size
    while (count != NULL)
    {
        size++;
        count = count->next;
    }
    // find k max
    while(true)
    {
        a = (a * 3) + 1;
        if (a > size)
            break;
        else
            k = a;
        //printf("k = %d\n", k);
    }

    List * listHead = malloc(sizeof(List));
    listHead -> node = list;
    listHead -> next = listHead;
    bool sortUp = false; // true is sort least to greatest, false is greatest to least

    while (k >= 1)
    {
        if (sortUp == false)
            sortUp = true;
        else 
            sortUp = false;
        listHead = createSublists(listHead, k, n_comp, sortUp);
        //printf("aaa\n");
        k = (k - 1) / 3;
    }
    list = listHead -> node;
    // testList(list);
    free(listHead);

    return list;
}
// create and sort sublists
static List * createSublists(List * listHead, int k, long * n_comp, bool sortUp)
{
    List * prevList = listHead;
    List * listptr; // traversal
    Node * node = NULL;
    //printf("\npointer to newList %p", (void*)newList);
    for(int i = 0; i < k; i++)
    {
        node = removeNode(&(prevList -> node));
        if (i == 0)
        {
            listHead = addList(node);
            listptr = listHead;
        }
        else
        {
            listptr -> next = addList(node);
            listptr = listptr -> next;

            if(node == NULL) // empty
            {
                prevList =  prevList ->next;
                break; 
            }
            node -> next = NULL;
            listptr -> node = node;
            //printf("%p\n", (void*)listptr);
        }
        prevList =  prevList -> next;
    }

    listptr -> next = listHead; // circular link
    if (k == 1) // sort upwards for last sort
        sortUp = true;
    // shell sort
    while(true)
    {
        node = removeNode(&( prevList -> node));
        listptr = listptr -> next;
        if(node == NULL)
            break;
        addAndSort(&(listptr ->node), node,n_comp, sortUp);
        prevList =  prevList -> next;
    }
    freeSubList(prevList);
    return listHead;
}
// add nodes to sublists and sort them
static void addAndSort(Node** head, Node* ins, long *n_comp, bool sortUp)
{
    Node * temp = NULL;
    temp = *head;
    (*n_comp)++;
    if (sortUp == true) // sort upward
    {
        if( ins -> value < (*head) -> value )
        {
            ins -> next = *head;
            (*head) = ins;
            return;
        }
        else
        {
            while((temp -> next != NULL) && (((temp -> next) -> value) < (ins -> value)))
            {
                temp = temp -> next;
                (*n_comp)++;
            }
        }
    }
    else // sort downward
    {
        if(ins -> value > (*head) -> value)
        {
            ins -> next = *head;
            (*head) = ins;
            return;
        }

        while((temp -> next != NULL) && (((temp -> next) -> value) > (ins -> value)))
        {
            temp = temp -> next;
            (*n_comp)++;
        }
    }
    ins -> next = temp -> next;
    temp -> next = ins;

    return;
}
static Node* removeNode(Node** head)
{
    if (*head == NULL)
    {
        return NULL;
    }
    else
    {
        Node * removed = *head;
        *head = (*head) -> next;
        removed -> next = NULL;

        return removed;
    }
}
// UNUSED TEST FUNCTION
/* static void testList(Node* head)
{
    int i = 0;
    while(head != NULL){
        i++;
        //fprintf(stderr, "node %d: %ld\n",i, head->value );
        head = head ->next;
        
    }
} 
*/

// free sub list nodes
static void freeSubList(List * subList){
    if(subList == NULL){
        return;
    }

    List * subListNext = subList -> next;
    if(subListNext == subList)
    {
        // empty
    }
    else
    {
        List * temp = NULL;
        while((subList != subListNext))
        {
            temp = subListNext;
            subListNext = subListNext -> next;
            free(temp);
        }
    }
    free(subList);
    return;
}