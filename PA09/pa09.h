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

char * read_File(FILE * fptr);
unsigned char CBMask(int myPos);
HuffNode * create_Node(int value);
Stack * stack_Push(Stack * head, HuffNode * myNode);
Stack * stack_Pop(Stack * head);
Stack * stack_peek(Stack * head);
Stack * stack_count(Stack * head);
#endif

