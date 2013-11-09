#ifndef PA09_H
#define PA09_H

typedef struct _huffnode {
    int value; 
    struct _huffnode * left;
    struct _huffnode * right;
} HuffNode;

typedef struct _stack {
    struct _stack * next;
    HuffNode * node;
} Stack;

unsigned char * read_File(FILE * fptr, int * myLength);
char * convert_Bin(unsigned char * myData);
#endif

