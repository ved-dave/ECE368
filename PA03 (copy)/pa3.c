#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pa3.h"

// create binary tree
Tree * buildTree(FILE * input, int numLn)
{
    fseek(input, 0, SEEK_SET); // reset fptr
	
    // reverse input file
    char **reversePo;
    reversePo = malloc(sizeof(char*)*numLn);
    for(int i = 0; i < numLn; i++)
    {
        reversePo[i] = malloc(sizeof(char)*15);
    }
    for(int i = 0; i < numLn; i++)
    {
        fgets(reversePo[i], 15, input);
    }

    Tree * binaryTree = NULL;
    binaryTree = malloc(sizeof(Tree));
    if (binaryTree ==  NULL)
    {
        return binaryTree;
    }
    fseek(input, 0, SEEK_SET);
    binaryTree -> root = constructor(reversePo, &numLn);
    free(reversePo);
    return binaryTree;
}

// build tree using reversed postorder str array "reversePo"
TreeNode * constructor(char ** reversePo, int * numLn) // FIX ME
{
    if (*numLn < 0)
    {
        return NULL;
    }
    TreeNode * tn = NULL;
    tn = malloc(sizeof(TreeNode));
    tn -> left = NULL;
    tn -> right = NULL;
    tn -> block = malloc(sizeof(Block));
    if (isdigit(reversePo[*numLn-1][0]) > 0)
    {
        char * token = strtok(reversePo[*numLn-1], "(");
        (tn -> block) -> label = atoi(reversePo[*numLn-1]);
        token = strtok(NULL, ",");
        (tn -> block) -> dims[0] = atoi(token);
        token = strtok(NULL, ")");
        (tn -> block) -> dims[1] = atoi(token);
        (tn -> block) -> coords[0] = 0;
        (tn -> block) -> coords[1] = 0;
        free(reversePo[*numLn - 1]);
    }
    else if(reversePo[*numLn-1][0] == 'V')
    {
        (tn -> block) -> label = -1;
        (tn -> block) -> dims[0] = 0;
        (tn -> block) -> dims[1] = 0;
        (tn -> block) -> coords[0] = 0;
        (tn -> block) -> coords[1] = 0;
        free(reversePo[*numLn - 1]);
    }
    else if(reversePo[*numLn-1][0] == 'H')
    {
        //printf("asdkkma\n");
        (tn -> block) -> label = -2;
        (tn -> block) -> dims[0] = 0;
        (tn -> block) -> dims[1] = 0;
        (tn -> block) -> coords[0] = 0;
        (tn -> block) -> coords[1] = 0;
        free(reversePo[*numLn - 1]);
    }
    else
    {
        return NULL;
    }
    if ((tn -> block) -> label < 1)
    {
        *numLn = *numLn -1;
        tn -> right = constructor(reversePo, numLn);
        *numLn = *numLn -1;
        tn -> left = constructor(reversePo, numLn);
    }
    return tn;
}

// print preorder traversal of tree and write to file
void printPreorder(TreeNode * root, FILE * input)
{
    if (root == NULL)
        return;
    // first recur on left subtree
    if((root -> block) -> label == -2)
    {
        fputc('H', input);
        fputc('\n', input);
    }
    else if((root -> block) -> label == -1)
    {
        fputc('V', input);
        fputc('\n', input);
    }
    else
    {
        fprintf(input, "%d", (root -> block) -> label);
        fputc('(', input);
        fprintf(input, "%d", (root -> block) -> dims[0]);
        fputc(',', input);
        fprintf(input, "%d", (root -> block) -> dims[1]);
        fputc(')', input);
        fputc('\n', input);
    }
    printPreorder(root->left, input);
    // then recur on right subtree
    printPreorder(root->right, input);
    // now deal with the node
}
// helper function for stackCompute
Block * compute(Block * left, Block * right, Block * letter)
{
    if (letter -> label == -1) // V
    {
        letter -> dims[0] = left -> dims[0] + right -> dims[0];
        letter -> dims[1] = ((left -> dims[1]) >= (right -> dims[1])) ? (left -> dims[1]) : (right -> dims[1]);
    }
    else // H
    {
        letter -> dims[1] = left -> dims[1] + right -> dims[1];
        letter -> dims[0] = ((left -> dims[0]) >= (right -> dims[0])) ? (left -> dims[0]) : (right -> dims[0]);
    }
    return letter;
}
// delete tree and add reversed post order strings to stack "dim". This will be reversed and printed later
void deleteTree(TreeNode * root, Stack * dim)
{
    if (root == NULL)
    {
        // basecase
        return;
    }
    //if (root -> block -> label > 0)
        //printf("%d(%d,%d)\n", root -> block -> label, root -> block -> coords[0], root -> block -> coords[1]);
    // first recur on left subtree
    char * str = malloc(sizeof(char) * 15);
    if((root -> block) -> label == -2)
    {
        /* fputc('H', dim);
        fputc('(', dim);
        fprintf(dim, "%d", (root -> block) -> dims[0]);
        fputc(',', dim);
        fprintf(dim, "%d", (root -> block) -> dims[1]);
        fputc(')', dim);
        fputc('\n', dim); */

        sprintf(str, "H(%d,%d)", (root -> block) -> dims[0], (root -> block) -> dims[1]);
    }
    else if((root -> block) -> label == -1)
    {
        /* fputc('V', dim);
        fputc('(', dim);
        fprintf(dim, "%d", (root -> block) -> dims[0]);
        fputc(',', dim);
        fprintf(dim, "%d", (root -> block) -> dims[1]);
        fputc(')', dim);
        fputc('\n', dim); */

        sprintf(str, "V(%d,%d)", (root -> block) -> dims[0], (root -> block) -> dims[1]);
    }
    else
    {
        /* fprintf(dim, "%d", (root -> block) -> label);
        fputc('(', dim);
        fprintf(dim, "%d", (root -> block) -> dims[0]);
        fputc(',', dim);
        fprintf(dim, "%d", (root -> block) -> dims[1]);
        fputc(')', dim);
        fputc('\n', dim); */

        sprintf(str, "%d(%d,%d)", (root -> block) -> label, (root -> block) -> dims[0], (root -> block) -> dims[1]);
    }
    push(dim, str);

    deleteTree(root -> right, dim);
    deleteTree(root -> left, dim);
    // then recur on right subtree
    free(root -> block);
    free(root);
}
// compute dimensions of each subblock V and H
void stackCompute(TreeNode * tn)
{
    if (tn -> block -> dims[0] != 0) // leaf node
    {
        // push(stack, tn -> block);
        //tn -> block -> coords[0] = 
        return;
    }
    //push(stack, tn -> block);
    stackCompute(tn -> right);
    stackCompute(tn -> left);

    //pop(stack);
    //pop(stack);
    //pop(stack);
    tn -> block = compute(tn -> left -> block, tn -> right -> block, tn -> block);
    //push(stack, tn -> block);
}
// print coordinates in post order traversal
 void printCoords(TreeNode * tn, FILE * pck)
{
    if (tn -> block -> label > 0) // leaf node
    {
        // push(stack, tn -> block);
        //tn -> block -> coords[0] = 
        fprintf(pck, "%d((%d,%d)(%d,%d))\n", tn -> block -> label, tn -> block -> dims[0], tn -> block -> dims[1], tn -> block -> coords[0], tn ->block -> coords[1]);
        return;
    }
    //push(stack, tn -> block);
    
    else if (tn -> block -> label == -2) // H
    {
        tn -> right -> block -> coords[0] = tn -> block -> coords[0];
        tn -> right -> block -> coords[1] = tn -> block -> coords[1];

        tn -> left -> block -> coords[1] = tn -> block -> coords[1] + tn -> right -> block -> dims[1];
        tn -> left -> block -> coords[0] = tn -> block -> coords[0];
        // printf("%d\n", tn -> right -> block -> dims[0]);
        // printf("%d\n", tn -> right -> block -> label);
        //printf("%d:(%d,%d)\n", tn -> left -> block -> label, tn -> left -> block -> coords[0], tn -> left -> block -> coords[1]);
        //printf("%d: (%d,%d)\n", tn -> right -> block -> label, tn -> right -> block -> coords[0], tn -> right -> block -> coords[1]);
        printCoords(tn -> left, pck);
        printCoords(tn -> right, pck);
    }
    else if(tn -> block -> label == -1) // V
    {
        tn -> left -> block -> coords[0] = tn -> block -> coords[0];
        tn -> left -> block -> coords[1] = tn -> block -> coords[1];

        tn -> right -> block -> coords[0] = tn -> block -> coords[0] + tn -> left -> block -> dims[0];
        tn -> right -> block -> coords[1] = tn -> block -> coords[1];
        //tn -> right -> block -> coords[1] = *yt - tn -> right -> block -> dims[1];
        //printf("%d: (%d,%d)\n", tn -> left -> block -> label, tn -> left -> block -> coords[0], tn -> left -> block -> coords[1]);
        //printf("%d: (%d,%d)\n", tn -> right -> block -> label, tn -> right -> block -> coords[0], tn -> right -> block -> coords[1]);
        printCoords(tn -> left, pck);
        printCoords(tn -> right, pck);
    }
    else
    {
        printCoords(tn -> left, pck);
        printCoords(tn -> right, pck);
    }
}
