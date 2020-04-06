#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// block
typedef struct rectangle
{
    int label; // -1 is V, -2 is H
    int dims[2]; // dims[0] = height , dims[1] = width
    int coords[2]; // coordinates [0] - x, [1] - y
} Block;

// tree node data
typedef struct tnode
{
  Block * block; // block info
  struct tnode * left;
  struct tnode * right;
} TreeNode;

// tree
typedef struct tree
{
  TreeNode * root;
} Tree;

// stackNode
typedef struct stacknode
{
  char * str;
  struct stacknode * next;
} StackNode;

// stakc
typedef struct stack
{
	StackNode * head;
} Stack;

// tree functions
Tree * buildTree(FILE * input, int numLn);
TreeNode * constructor(char ** reversePo, int * numLns);
void printPreorder(TreeNode * root, FILE * input);
void deleteTree(TreeNode * root, Stack * dim);
void stackCompute(TreeNode * tn);
void printCoords(TreeNode * tn, FILE * pck);
Block * compute(Block * left, Block * right, Block * letter);

// stack functions
Stack * createStack();
void push(Stack* stack, char * str);
char * pop(Stack* stack);
void reverseFile(Stack * stack, FILE * output);
