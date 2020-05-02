#include "hbt.h"
#include <stdbool.h>

// general
void deleteTree(Tnode * root);
Tnode * new(int key);
void write(Tnode *root, FILE * fptr);

// evalualte
void evaluate(FILE * fptr);
Tnode *buildEvalTree(int * keyarr, char * nodeid, int size, int * index);
bool bst(Tnode * root);
bool hb(Tnode * root);
int calcbalance(Tnode * root, bool * isHB);

// construct
Tnode * buildAVL(FILE * input, FILE * output);

// rotate
Tnode * rotateRight(Tnode * root);
Tnode * rotateLeft(Tnode * root);
Tnode * rotateRL(Tnode * root);
Tnode * rotateLR(Tnode * root);

// ins/del
Tnode * insert(Tnode * root, int key, char * bal);
Tnode * delete(Tnode * root, int key, char * bal);
