#include <stdio.h>
#include <stdlib.h>
#include "pa09.h"

char * read_File(FILE * fptr)
{
  int myArrSize = 0;
  int arrPos = 0;
  int CBLoc = 0;
  int myFlag1 = 0;
  int myFlag2 = 0; //flag for if char still needs to be read in
  int myZeroCt = 0;

  while(fgetc(fptr) != 0x0A)
    {
      myArrSize++;
    }
  
  char * myData = malloc(((myArrSize * 2) + 8) * sizeof(char));
  
  if(myData == NULL)
    {
      return NULL;
    }

  fseek(fptr, 0, SEEK_SET);

  unsigned char myByte = 0x00;

  myByte = fgetc(fptr);
  
  if(myByte == '1') //see if the file is binary or char based
    {
      myFlag2 = 1;
    }

  myFlag1 = ungetc(myByte, fptr);

  if(myFlag1 == EOF)
    {
      return NULL;
    }

  while(myByte != 0x0A)
    {
      myByte = fgetc(fptr);  //opens 1 byte of information from the input file
      fpos_t myPrevFPos;
      myFlag1 = fgetpos(fptr, &myPrevFPos); //flag to make sure getPos doesn't error
      CBLoc = (CBLoc % 8);  //keep Command Bit Location inside the byte

      if(myFlag1 != 0)
	{
	  return NULL;
	}

      if(!myFlag2)
        {

	  if((CBMask(CBLoc) & myByte) == 0)
	    { 
	      if(myZeroCt == 0) //if the previous char read in was a 0
		{
		  myData[arrPos] = '0';
		  arrPos++;
		  CBLoc++;
		  myZeroCt++;
     
		  myFlag1 = ungetc(myByte, fptr);

		  if(myFlag1 == EOF)
		    {
		      return NULL;
		    }
		}
	      else
		{
		  while(CBLoc < 8)
		    {
		      myData[arrPos] = '0';
		      arrPos++;
		      CBLoc++;
		    }
		  myFlag2 = 1;
		}

	    }
	  else
	    {
	      unsigned char myNByte = fgetc(fptr);

	      if(CBLoc != 7)
		{
		  myFlag1 = fsetpos(fptr, &myPrevFPos);

		  if(myFlag1 != 0)
		    {
		      return NULL;
		    }
		}

	      unsigned char c1 = myByte << (CBLoc + 1);
	      unsigned char c2 = myNByte >> (7 - CBLoc);

	      myData[arrPos] = '1';
	      arrPos++;
	      myData[arrPos] = (c1 + c2);
	      arrPos++;
	      myZeroCt = 0;
	      CBLoc++;
	    }
	}
      else
	{
	  myData[arrPos] = myByte;
	  arrPos++;
	}
    }

  return myData;
}

unsigned char CBMask(int myPos)
{
  unsigned char myMask = 0x80;
  myMask >>= (myPos % 8);
  return myMask;
}

HuffNode * create_Node(int value)
{
  HuffNode * myNode = NULL;
  myNode = malloc(sizeof(myNode));
  
  if(myNode == NULL)
    {
      return NULL;
    }
  
  myNode -> value = value;
  myNode -> left = NULL;
  myNode -> right = NULL;
  
  return myNode;
}

Stack * stack_Push(Stack * head, HuffNode * myNode)
{
  Stack * myNewHead = NULL;
  myNewHead = malloc(sizeof(Stack));
  if(myNewHead == NULL)
    {
      return NULL;
    }
  myNewHead -> node = myNode;
  myNewHead -> next = head;
  return myNewHead;
}

Stack * stack_Pop(Stack * head, HuffNode ** myNode)
{
  *myNode = head -> node;
  Stack * myNewHead = head -> next;
  free(head);
  return myNewHead;
}

HuffNode * stack_Peek(Stack * head)
{
  return head -> node;
}

int stack_Count(Stack * head)
{
  if(head == NULL)
    {
      return 0;
    }
  
  return stack_Count(head -> next) + 1;
}

HuffNode * create_HuffTree(char * myData)
{
  int myFlag1 = 0;  //asserts if the tree is created
  int i = 0;
  Stack * myStack = NULL;

  while(!myFlag1)
    {
      if(myData[i] == 49) //ascii value of 1 is 49
	{
	  i++;
	  HuffNode * myValue = create_Node(myData[i]);
	  myStack = stack_Push(myStack, myValue);
	  i++;
	}
      else if(myData[i] == 48) //ascii value of 0 is 48
	{
	  int myCount = stack_Count(myStack);
	  if(myCount == 1)
	    {
	      HuffNode * myTree = myStack -> node;
	      free(myStack);
	      myFlag1 = 1;
	      return myTree;
	    }
	  else if(myCount > 1)
	    {
	      HuffNode * myNode1 = NULL;
	      HuffNode * myNode2 = NULL;
	      myStack = stack_Pop(myStack, &myNode1);
	      myStack = stack_Pop(myStack, &myNode2);
	      HuffNode * myParent = create_Node(0);
	      myParent -> right = myNode1;
	      myParent -> left = myNode2;
	      myStack = stack_Push(myStack, myParent);
	    }
	  else
	    {
	      return NULL;
	    }
	  i++;
	}
      else
	{
	  return NULL;
	}
    }

  return NULL;

}

void Huff_postOrderPrint(HuffNode *tree)
{
    // Base case: empty subtree
    if (tree == NULL) {
		return;
    }

    // Recursive case: post-order traversal

    // Visit left
    printf("Left\n");
    Huff_postOrderPrint(tree->left);
	printf("Back\n");
    // Visit right
    printf("Right\n");
    Huff_postOrderPrint(tree->right);
	printf("Back\n");
    // Visit node itself (only if leaf)
    if (tree->left == NULL && tree->right == NULL) {
		printf("Leaf: %c\n", tree->value);
    }
    

}


void destroy_helper(HuffNode * array)
{
  if(array -> left != NULL)
    {
      destroy_helper(array -> left);
    }
  if(array -> right != NULL)
    {
      destroy_helper(array -> right);
    }

  free(array);

  return;
}

void HuffTree_destroy (HuffNode * array)
{
  if(array != NULL)
    {
      destroy_helper(array);
    }
}
