#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <values.h>
#include "huffman.h"

TreeNode  * makeTreeNode(int value, int frequency){
    TreeNode * tn = malloc(sizeof(TreeNode));
    tn->left = NULL;
    tn->right = NULL;
    tn->value = value;
    tn->frequency = frequency;
    return tn;
} //create tree
ListNode * makeListNode(TreeNode * tn){
    ListNode * ln = malloc(sizeof(ListNode));
    ln->next = NULL;
    ln->root = tn;
    return ln;
} //create linked list

ListNode * insert(ListNode * head, ListNode * ln){
    if (head == NULL){
        return ln;
    }
    if (ln == NULL || ln->next != NULL){
        printf("error\n");
    }
    if ((head->root)->frequency <= (ln->root)->frequency){
        head->next = insert(head->next, ln);
        return head;
    }
    ln->next = head;
    return ln;
}

ListNode * construct(long * arr, FILE * output){
    int ind = 0;
    while (arr[ind] == 0){
        ind++;
    }
    if (ind == 256){ //no frequency
        return NULL;
    }
    
    ListNode * head = NULL;
    while (ind < 256){
        if (arr[ind])
        {
            TreeNode * tree = makeTreeNode(ind, arr[ind]);
            ListNode * node = makeListNode(tree);
            head = insert(head, node);
        }
        ind ++;
    }

    while ((head -> next) != NULL)
    { //merge linked list to a tree
        ListNode * num2 = head->next;
        ListNode * num3 = num2->next;
        TreeNode * tn1 = head->root;
        TreeNode * tn2 = num2->root;
        free(head);
        free(num2);
        head = num3;
        TreeNode * merg = malloc(sizeof(TreeNode));
        merg->left = tn1;
        merg->right = tn2;
        merg->value = 0;
        merg->frequency = tn1->frequency+tn2->frequency;
        ListNode * ln = makeListNode(merg);
        head = insert(head, ln);
    }
    printTree(head->root, output);
    return head;
}

void printTree (TreeNode * tn, FILE *output){
    if (tn == NULL){
        return;
    }
    TreeNode * lc = tn->left;
    TreeNode * rc = tn->right;
    if ((lc==NULL) && (rc==NULL)){
        //printf("%c", tn->value);
        fprintf(output, "1%c", (char)tn->value);
        return;
    }
    else{
        fprintf(output, "0");
    }
    printTree(lc, output);
    printTree(rc, output);
    return;
}

void deleteTree (TreeNode * root){
    if (root == NULL){
        return;
    }
    else
    {           
        deleteTree(root->left);
        deleteTree(root->right);
        free(root);
        return;
    }
}