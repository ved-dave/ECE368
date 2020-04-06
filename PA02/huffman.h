
#ifndef huffman_H
#define huffman_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// huffman tree structure
typedef struct tnode
{
  int value;
  int frequency;
  struct tnode * left;
  struct tnode * right;
} TreeNode;

// linked list node structure
typedef struct listnode
{
  TreeNode * root;
  struct listnode * next;
} ListNode;

typedef struct{
    int l; //number of elements
    int code[256];
} huffmanStruct;

TreeNode  * makeTreeNode(int value, int freq);
ListNode * makeListNode(TreeNode * tn);
ListNode * insert(ListNode * head, ListNode * ln);
ListNode * construct(long * arr, FILE * output);
void printTree (TreeNode * ln, FILE *output);
void deleteTree (TreeNode * root);
void encoder(TreeNode * tn, int *arr, huffmanStruct * code, FILE *output, int l);
long treeCharCount(FILE * treeData, FILE * output);
long compress(huffmanStruct * code, FILE * input, FILE * output, long numcomp);

#endif

