#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pa4.h"
#include "hbt.h"

Tnode * buildAVL(FILE * input, FILE * output)
{    
    // empty
	fseek (input, 0, SEEK_END);
    int filesize = ftell(input);
    if (!filesize)
    {
        printf("0\n");
        return NULL;
    }

	fseek(input, 0, SEEK_SET);
    int key;
    char op;
    int cnt = 0;
    do
    {
        int readKey = fread(&key, sizeof(int), 1, input);
        if(feof(input))
        {
            break;
        }
        if (readKey != 1)
        {
            printf("0\n");
            return NULL;
        }
        int readOp = fread(&op, sizeof(char), 1, input);
        if(readOp != 1)
        {
            printf("0\n");
            return NULL;
        }
        if(feof(input))
        {
            break;
        }
        cnt++;
    } while (true);

    Tnode * root = NULL;
    char insbal = 'n';
    char delbal = 'n';

	fseek(input, 0, SEEK_SET);

    for(int i = 0; i < cnt; i++)
    {   
        (void) (fread(&key, sizeof(int), 1, input) + 1);
        (void) (fread(&op, sizeof(char), 1, input) + 1);
		if (op == 'd')
        {
			root = delete(root, key, &delbal);
        }
        else if(op == 'i')
		{
			root = insert(root, key, &insbal);
		}
		else 
		{
			printf("0\n");
            return root;
		}
    }
	printf("1\n");
	return root;
}


Tnode *insert(Tnode *root, int key, char * bal)
{
	if(root == NULL)
	{
		*bal = 'n';
		Tnode *newNode = new(key);
		if(newNode == NULL)
		{
			fprintf(stdout, "0\n");
		}
		return newNode;
	}
	*bal = 'y';

    if (root -> key < key)
	{
		root->right = insert(root->right, key, bal);
		if(*bal == 'n')
		{
			root->balance --;
		}
		if(root->balance == 0)
		{
			*bal = 'y';
		}
	}
	else
	{
		root->left = insert(root->left, key, bal);
		if(*bal == 'n')
		{
			root->balance ++;
		}
		if(root->balance == 0)
		{
			*bal = 'y';
		}
	}

	if(root->balance == 2)
	{
		Tnode *leftNode = root->left;
		if(leftNode->balance == 1)
		{
			root = rotateRight(root);
			root->balance = 0;
			(root->right)->balance = 0;
		}
		if(leftNode->balance == -1)
		{
			root = rotateLR(root);
		}
		*bal = 'y';		
	}
	if(root->balance == -2)
	{
		Tnode *rightNode = root->right;
		if(rightNode->balance == -1)
		{
			root = rotateLeft(root);
			root->balance = 0;
			(root->left)->balance = 0;
		}
		if(rightNode->balance == 1)
		{
			root = rotateRL(root);
		}
		*bal = 'y';
	}

	return root;
}

Tnode *delete(Tnode *root, int key, char * bal)
{
	if(root == NULL)
	{
		return root;
	}

	*bal = 'y';
    if(root -> key > key)
	{
		root->left = delete(root->left, key, bal);
		if(*bal == 'n')
		{
			root -> balance--;
		}
		if(root->balance == -1)
		{
			*bal = 'y';
		}
	}
	else if(root -> key < key)
	{
		root->right = delete(root->right, key, bal);
		if(*bal == 'n')
		{
			root->balance ++;
		}
		if(root->balance == 1)
		{
			*bal = 'y';
		}
	}
	else
	{
        if (root -> left == NULL || root -> right == NULL)
        {
            Tnode * todelete = root;
            if ((root -> right == NULL) && (root -> left == NULL))
            {
                root = NULL;
            }
            else if (root -> left == NULL)
            {
                root = root -> right;
            }
            else
            {
                root = root -> left;
            }

            free(todelete);
            *bal = 'n';
            return(root);
        }
        else
        {
            Tnode *predecessor = root->left;
            while((predecessor -> right != NULL))
            {
                predecessor = predecessor->right;
            }
            root->key = predecessor->key;
            predecessor->key = key + 1;
            root->left = delete(root->left, key + 1, bal);
            if(*bal == 'n')
            {
                root -> balance--;
            }
            if(root->balance == -1)
            {
                *bal = 'y';
            }
        }
	}

	if(root->balance == 2)
	{
		Tnode *leftNode = root->left;
		if(leftNode->balance == 1)
		{
			root = rotateRight(root);
			root->balance = 0;
			(root->right)->balance = 0;
			*bal = 'y';
		}
		else if(leftNode->balance == -1)
		{
			root = rotateLR(root);
            if (root -> left -> left != NULL)
            {
                *bal = 'y';
            }
		}
		else if(leftNode->balance == 0)
		{
			root = rotateRight(root);
			root->balance = -1;
			(root->right)->balance = 1;
			*bal = 'y';
		}
	}
	if(root->balance == -2)
	{
		Tnode *rightNode = root->right;
		if(rightNode->balance == -1)
		{
			root = rotateLeft(root);
			root->balance = 0;
			(root->left)->balance = 0;
			*bal = 'y';
		}
		else if(rightNode->balance == 1)
		{
			root = rotateRL(root);
            if (root -> right -> right != NULL)
            {
                *bal = 'y';
            }
		}
		else if(rightNode->balance == 0)
		{
			root = rotateLeft(root);
			root->balance = 1;
			(root->left)->balance = -1;
			*bal = 'y';
		}
	}

	return root;
}

// rotate right or clockwise
Tnode *rotateRight(Tnode *root)
{
	Tnode * newRoot = root->left;
	Tnode * temp = newRoot -> right;
	newRoot -> right = root;
	root -> left = temp;

	return newRoot;
}
// rotate left or counter clockwise
Tnode *rotateLeft(Tnode *root)
{
	Tnode * newRoot = root-> right;
	Tnode * temp = newRoot -> left;
	newRoot -> left = root;
	root -> right = temp;

	return newRoot;
}

// rightleft rotation
Tnode * rotateRL(Tnode * root)
{
    root->right = rotateRight(root->right);
	root = rotateLeft(root);
	if((root->right)->right == NULL)
	{
		(root->left)->balance = 0;
		(root->right)->balance = 0;
	}
	if(root->balance == 1)
	{
		root->balance = 0;
		(root->left)->balance = 0;
		(root->right)->balance = -1;	
	}
	if(root->balance == -1)
	{
		root->balance = 0;
		(root->left)->balance = 1;
		(root->right)->balance = 0;
    }
    return root;
}
// left right rotation
Tnode * rotateLR(Tnode * root)
{
    root->left = rotateLeft(root->left);
	root = rotateRight(root);
    if((root->left)->left == NULL)
	{
		(root->left)->balance = 0;
		(root->right)->balance = 0;
	}
	if(root->balance == 1)
	{
	    root->balance = 0;
		(root->left)->balance = 0;
		(root->right)->balance = -1;
	}
	if(root->balance == -1)
	{
		root->balance = 0;
		(root->left)->balance = 1;
		(root->right)->balance = 0;
	}
    return root;
}