#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <values.h>
#include "huffman.h"

void encoder(TreeNode * tn, int *ASCII, huffmanStruct * code, FILE *output, int l)
{
    if (tn == NULL)
    {
        return;
    }
    else
    {
        TreeNode * lc = tn -> left;
        TreeNode * rc = tn -> right;
        if ((lc && rc) == 0) // if node are leaf nodes
        {
            fprintf(output, "%c:", tn->value);
            int i; // counter
            
            for(i = 0; i < l; i++)
            {
                code[(int)tn->value].code[i] = ASCII[i];
                fprintf(output, "%d", code[(int)tn->value].code[i]); // copy char cnt to the huffman struct array
            }
            code[(int)tn->value].l = l;
            fprintf(output, "\n");

            return;
        }
        else
        {
            encoder(lc, ASCII, code, output, l + 1); // preorder traversal
            ASCII[l] = 1;
            encoder(rc, ASCII, code, output, l + 1);
            ASCII[l] = 0;
        }
    }
}

long treeCharCount(FILE * treeData, FILE * output)
{


    fseek(treeData, 0, SEEK_SET);
    int countTree = 0;
    while (fgetc(treeData)!=EOF){
        countTree ++;
    }

    long numTree = 0; // elem in tree
    int check = 0; // checker (0 or 1)
    int cont = 0; // continue
    int i = 0; // count
    int g1 = 0; // get one
    unsigned char topography = 0; // char in tree
    unsigned char ifr = 0;
    unsigned char mask; //masked character


    fseek(treeData, 0, SEEK_SET);
    do 
    {
        topography = fgetc(treeData);
        if (i == countTree)
        {
            ifr = ifr | (0X00 << cont);
            fwrite(&ifr, sizeof(unsigned char), 1, output);
            numTree ++;
            break;
        }
        if (topography == 0X30 && !g1)
        {
            ifr = ifr | 0X00 << cont;
            cont ++;
            check = 0;
        }
        else if (topography == 0X31 && !g1)
        {
            ifr |= 0X01 << cont;
            cont ++;
            check = 0;
            g1 = 1;
        }
        else if (check)
        {
            fwrite(&topography, sizeof(unsigned char), 1, output);
            numTree ++;
            check = 0;
            g1 = 0;
        }
        else 
        {
            mask = 0XFF;
            mask = mask >> (cont);
            ifr = ifr | (mask & topography) << (cont);
            fwrite(&ifr, sizeof(unsigned char), 1, output);
            numTree ++;
            ifr = 0;
            ifr |= topography >> (8-cont);
            g1 = 0;
        }

        if (cont == 8){
            cont = 0;
            fwrite(&ifr, sizeof(unsigned char), 1, output);
            numTree ++;
            ifr = 0;
            check = 1;
        }
        i++;
    } while (i <= countTree);

    return numTree;
}

long compress(huffmanStruct * code, FILE * input, FILE * output, long compChar){
    fseek(input, 0, SEEK_SET);
    int i;
    unsigned char origin = 0;
    int cont = 0;
    while((i = fgetc(input)) != EOF){
        for (int j = 0; j < code[abs(i)].l; j++)
        {
            if (code[abs(i)].code[j]){
                origin |= 0X01 << (cont);
            }
            cont++;
            if (cont == 8) // long sz
            {
                fwrite(&origin, sizeof(unsigned char), 1, output);
                compChar++;
                origin = 0;
                cont = 0;
            }
        }
    }
    if (cont){
        fwrite(&origin, sizeof(unsigned char), 1, output);
        compChar++;
    }
    return compChar;
}