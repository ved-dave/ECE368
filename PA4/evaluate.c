#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "pa4.h"
#include "hbt.h"

void evaluate(FILE * fptr)
{
	
	// empty
	fseek (fptr, 0, SEEK_END);
    int filesize = ftell(fptr);
    if (!filesize)
    {
        printf("0,0,0\n");
        return;
    }

	// read
	int key;
	char child;
	int cnt = 0;
	
	fseek(fptr, 0, SEEK_SET);
	do
	{
		int readkey = fread(&key, sizeof(int), 1, fptr);
        if(feof(fptr))
		{
            break;
		}
		else if (readkey < 1 || readkey > 1)
		{
			printf("0,0,0\n");
			return;
		}
        int readchild = fread(&child, sizeof(char), 1, fptr);
		if (readchild < 1 || readchild > 1)
		{
			printf("0,0,0\n");
			return;
		}
		else if (child < 0 || child > 3)
		{
			printf("0,0,0\n");
			return;
		}
		cnt++;
		if(feof(fptr))
		{
        	break;
		}
	} while(true);

	fseek(fptr, 0, SEEK_SET);

	int * keyarr = malloc(cnt * sizeof(int));
	char * childarr = malloc(cnt * sizeof(char));

	for(int i=0; i<cnt; i++)
	{
		(void) (fread(&keyarr[i], sizeof(int), 1, fptr) + 1);
        (void) (fread(&childarr[i], sizeof(char), 1, fptr) + 1); // the +1 is to ignore compier errors
	}

	int index = 0;

	Tnode * root = buildEvalTree(keyarr, childarr, cnt, &index);
	if(root != NULL)
	{
		fprintf(stdout, "1,%d,%d\n", bst(root), hb(root));
		deleteTree(root);	
	}
	free(keyarr);
	free(childarr);
	return;
}
 
bool bst(Tnode *root)
{
	if(root != NULL)
	{
		if (root -> right != NULL && (root -> key > (root -> right -> key)))
		{
			return false;
		}
		else if (root->left != NULL && (root -> key < (root -> left -> key)))
		{
			return false;
		}
		else if((!bst(root->right)))
		{
			return false;
		}
		else if (!bst(root->left))
		{
			return false;
		}
	}
	return true; 
}

// height balance
bool hb(Tnode * root)
{
	bool hb = 1;
	calcbalance(root, &hb);

	return hb;
}
// calculate balance of root
int calcbalance(Tnode *root, bool *isHB)
{
	int balance = 0;
	if(root != NULL)
	{
		int rb = calcbalance(root -> right, isHB);
		int lb = calcbalance(root -> left, isHB);

		root -> balance = rb - lb;
		if(root -> balance != 1 && root -> balance != 0 && root -> balance != -1)
		{
			*isHB = false;
		}
		if (rb > lb)
		{
			balance = rb;
		}
		else
		{
			balance = lb;
		}
		balance++;
	}
	return balance;
}

Tnode *buildEvalTree(int * keyarr, char * nodeid, int size, int * index)
{
	Tnode * node = NULL;
	if(size != (*index))
	{
		node = new(keyarr[*index]);
		if(node == NULL)
		{
			fprintf(stderr, "malloc failed.");
			return node;
		}
		int prevIndex = *index;
		(*index)++;
		
		if((nodeid[prevIndex] == 2) || (nodeid[prevIndex] == 3))
		{
			node->left = buildEvalTree(keyarr, nodeid, size, index);
		}
		if((nodeid[prevIndex] == 1) || (nodeid[prevIndex] == 3))
		{
			node->right = buildEvalTree(keyarr, nodeid, size, index);
		}
	}
	return node;
}

