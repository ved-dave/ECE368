#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pa3.h"

int main(int argc, char * argv[])
{
    if (argc != 5)
    {
        // incorrect input
        return EXIT_FAILURE;
    }
    FILE * input = fopen(argv[1], "r");
    FILE * out1 = fopen(argv[2], "w");
    FILE * out2 = fopen(argv[3], "w");
    FILE * out3 = fopen(argv[4], "w");
    //FILE * tempPr = fopen("temppr.txt", "w+");
    //FILE * tempDim = fopen("tempdim.txt", "w+");
    //FILE * tempPck = fopen("temppck.txt", "r+");

    // create tree from input
    int numLn = 0; // number of lines
    char c[15]; // first char of line

    while (fgets(c, 15, input) != NULL) // count num of lines and check input file for errors
    {
        numLn++;
        if (!isdigit(c[0]) && c[0] != 'H' && c[0] != 'V')
        {
            return EXIT_FAILURE;
        }
    }
    Tree * binaryTree = NULL;
    binaryTree = buildTree(input, numLn);

    if (binaryTree == NULL)
    {
        fclose(input);
        fclose(out1);
        fclose(out2);
        fclose(out3);
        return EXIT_FAILURE;
    }

    // part 1
    //FILE * temp = fopen("temp.")
    printPreorder(binaryTree -> root, out1);

    // part 2
    stackCompute(binaryTree -> root);

    // part 3
    printCoords(binaryTree -> root, out3);

    Stack * dim = createStack();
    deleteTree(binaryTree -> root, dim);
    reverseFile(dim, out2);

    free(binaryTree);
    fclose(input);
    fclose(out1);
    fclose(out2);
    fclose(out3);
    return EXIT_SUCCESS;
}
