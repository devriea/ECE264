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
Stack * stack_Pop(Stack * head, HuffNode ** myNode);
HuffNode * stack_Peek(Stack * head);
int stack_Count(Stack * head);
HuffNode * create_HuffTree(char * myData);
void Huff_postOrderPrint(HuffNode * tree, FILE * fptr);
void destroy_helper(HuffNode * array);
void HuffTree_destroy(HuffNode * array);
#endif

