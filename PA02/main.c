#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <values.h>
#include "huffman.h"


long count(long * ASCII, FILE * inputFile, FILE * countFile);

// main function
int main(int argc, char* argv[])
{
    // Define i/o files
    FILE * inputFile = fopen(argv[1], "r"); // open input file
    FILE * countFile = fopen(argv[2], "w"); // open input file
    FILE * treeFile = fopen(argv[3], "w+"); // tree topology file
    FILE * huffmanFile = fopen(argv[4], "w"); // huffman code file
    FILE * compressedFile = fopen(argv[5], "w"); // compressed output file

    if ((inputFile == NULL) || (countFile == NULL) || (treeFile == NULL) || (huffmanFile == NULL) || (compressedFile == NULL))
    {
        // printf("file read error")
            // close file pointers
        fclose(inputFile);
        fclose(countFile);
        fclose(treeFile);
        fclose(huffmanFile);
        fclose(compressedFile);

        return EXIT_FAILURE;
    }

    long treeChar = 0; // # of characters storing huffman topology
    long compChar = 24; // # of characters in huffman compressed file
    long ASCII[256] = {0}; // ascii character chart

    long origChar = count(ASCII, inputFile, countFile); // count each character and output file, along with populating the array. return no. of characters.

    fwrite(&compChar, sizeof(long), 1, compressedFile);
    fwrite(&treeChar, sizeof(long), 1, compressedFile);
    fwrite(&origChar, sizeof(long), 1, compressedFile);

    ListNode * head = NULL;
    head = construct(ASCII, treeFile); //generate linked list

    if (head == NULL) // list empty
    {
        if (fgetc(inputFile) == -1) // if original file is empty, then no list build errors
        {
            fclose(inputFile);
            fclose(countFile);
            fclose(treeFile);
            fclose(huffmanFile);
            fclose(compressedFile);

            return EXIT_SUCCESS;
        }
        else
        {
            fclose(inputFile);
            fclose(countFile);
            fclose(treeFile);
            fclose(huffmanFile);
            fclose(compressedFile);

            return EXIT_FAILURE; // list build error
        }
    }

    //build huffman code
    TreeNode * root = head -> root;
    free(head); //no need for listnode
    int arrcode[256] = {0};
    huffmanStruct * code = NULL;
    code = malloc(sizeof(huffmanStruct) * 256);

    encoder(root, arrcode, code, huffmanFile, 0);


    //compress the file
    treeChar = treeCharCount(treeFile, compressedFile);
    compChar += compress(code, inputFile, compressedFile, 0) + treeChar;
    fseek(compressedFile, 0, SEEK_SET);
    fwrite(&compChar, sizeof(long), 1, compressedFile);
    fwrite(&treeChar, sizeof(long), 1, compressedFile);
    fwrite(&origChar, sizeof(long), 1, compressedFile);

    //free memory
    free(code);
    deleteTree(root);
    fclose(inputFile);
    fclose(countFile);
    fclose(treeFile);
    fclose(huffmanFile);
    fclose(compressedFile);

    return EXIT_SUCCESS;
}

// count function
long count(long * ASCII, FILE * inputFile, FILE * countFile)
{
    int asciiValue = (int)fgetc(inputFile);
    long cnt = 0;

    while (asciiValue != EOF) // populate array with counts of each character
    {
        if (asciiValue < 256)
        {
            ASCII[asciiValue]++;
            asciiValue = (int)fgetc(inputFile);
            cnt++;
        }
    }

    fwrite(ASCII, sizeof(long), 256, countFile); // write ascii array data to file.

    return cnt;
}

// void closeFptr(inp)