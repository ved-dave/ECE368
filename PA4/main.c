#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hbt.h"
#include "pa4.h"

int main (int argc, char *argv[])
{
    if (argc < 3)
    {
        return EXIT_FAILURE;
    }

    FILE * input = fopen(argv[2], "r");

    if (!(strcmp(argv[1], "-e")))
    {
        if (input == NULL)
        {
            printf("-1,0,0\n");
            fclose(input);
            return EXIT_FAILURE;
        }
        else
        {
            evaluate(input);
        }
    }
    else if (!(strcmp(argv[1], "-b")))
    {
        if (input == NULL)
        {
            printf("-1\n");
            fclose(input);
            return EXIT_FAILURE;
        }
        FILE * output = fopen(argv[3], "w");
        if (output == NULL)
        {
            printf("-1\n");
            fclose(input);
            return EXIT_FAILURE;
        }
        else
        {
            Tnode * root = buildAVL(input, output);
			write(root, output);
			deleteTree(root);
        }
        
        fclose(output);
    }
    else
    {
        fclose(input);
        return EXIT_FAILURE;
    }
    
    fclose(input);
    return EXIT_SUCCESS;
}
// common tree funcs between eval and construct
Tnode *new(int key)
{
    Tnode * tn = malloc(sizeof(Tnode));
    tn -> balance = 0;
    tn -> key = key;
    tn -> left = NULL;
    tn -> right = NULL;

    return tn;
}

void deleteTree(Tnode *root)
{
	if(root)
	{
		deleteTree(root->left);
		deleteTree(root->right);
		free(root);
	}
}

void write(Tnode *root, FILE *fptr)
{
	if(root != NULL)
	{
		char nodeid;
		if(root -> left != NULL && root -> right != NULL)
		{
			nodeid = 3;
		}
		else if(root -> left != NULL)
		{
			nodeid = 2;
		}
		else if(root->right != NULL)
		{
			nodeid = 1;
		}
		else
		{
			nodeid = 0;
		}
		
		fwrite(&(root->key), sizeof(int), 1, fptr);
		fwrite(&nodeid, sizeof(char), 1, fptr);

		write(root->left, fptr);
		write(root->right, fptr);
	}
}
