#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pa3.h"
 // stack for reversing post order outputs
Stack * createStack()
{
    Stack * stack = malloc(sizeof(Stack));
    stack -> head = NULL;
    return stack;
}
// push string
void push(Stack* stack, char * str)
{
    if (stack == NULL)
    {
        //printf("error: stack does not exist\n");
        return;
    }

    else
    {
        StackNode * node = NULL;
        node = malloc(sizeof(StackNode));
        node -> next = stack -> head;
        stack -> head = node;
        stack -> head -> str = str;
    }
    //printf("pushed ""%s"" to stack\n", stack -> head -> str);
    return;
}
// pop string
char * pop(Stack* stack)
{
    char * popStr = stack -> head -> str;
    StackNode * popNode = stack -> head;
    stack -> head = stack -> head -> next;
    free(popNode);

    //printf("popped ""%s"" from stack\n", popStr);

    return popStr;
}
// reverse strings in ouptut
void reverseFile(Stack * stack, FILE * output)
{
    while (stack -> head != NULL)
    {
        char * str = pop(stack);
        fprintf(output, "%s\n", str);
        free(str);
    }
    free(stack);
    return;
}