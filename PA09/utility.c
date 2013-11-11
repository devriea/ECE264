#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pa09.h"
#define CH_ZERO 48 //ascii value of '0' is 48
#define CH_ONE 49  //ascii value of '1' is 49

/* This function determines if the file we are reading
 * is a char-based input file or a bit-based input file
 * and gives an output indicating which is the case.
 */
int isFileChar(char * myFileName)
{
  char * isChar = strstr(myFileName, "_ch");
  if(isChar == NULL)
    {
      return 0;
    }
  else
    {
      return 1;
    }
}

/* This function is thing of beauty, it handles both bit-based
 * input and char based input very well, and can distinguish
 * how it needs to read the file thanks to the function 
 * isFileChar. Once it knows whether the file is bit-based
 * or char-based, it reads the file in accordingly to an array
 * of chars, then returns the completed array.
 */
char * read_File(FILE * fptr, char * myFileName)
{
  int myArrSize = 0; //Size of Array
  int arrPos = 0;    //Location in Array
  int CBLoc = 0;     //location of CommandBit
  int myFlag1 = 0;   //error checking flag
  int myFlag2 = 0;   //flag for if file is bit or byte based

  while(fgetc(fptr) != EOF)
    {
      myArrSize++;
    }
  
  /* memory allocation is for worst case scenario of bit based input
   * with nothing but 0's to store.*/

  char * myData = malloc((myArrSize * 8) * sizeof(char));
  
  if(myData == NULL)
    {
      return NULL;
    }

  fseek(fptr, 0, SEEK_SET);

  unsigned char myByte = 0x00;
  
  myFlag2 = isFileChar(myFileName); //see if the file is binary or char based

  while(!feof(fptr))
    {
      myByte = fgetc(fptr);  //opens 1 byte of information from the input file
      fpos_t myPrevFPos;
      myFlag1 = fgetpos(fptr, &myPrevFPos); //flag to make sure getPos doesn't error
      CBLoc = (CBLoc % 8);  //keep Command Bit Location inside the byte

      if(myFlag1 != 0)  //fgetpos returns 0 if successful
	{
	  return NULL;
	}

      if(!myFlag2) //myFlag2 is asserted if we need to read bits
        {

	  if((CBMask(CBLoc) & myByte) == 0) //if we read a zero for the command bit
	    { 
	      myData[arrPos] = '0'; //we store a zero on the char array
	      arrPos++;
		  
	      if(CBLoc != 7)                  //if there is no leftover data on the current byte
		{                             //don't put it back
		  myFlag1 = ungetc(myByte, fptr); 

		  if(myFlag1 == EOF) //error checking
		    {
		      return NULL;
		    }
		}

	      CBLoc++;

	    }
	  else
	    {
	      unsigned char myNByte = fgetc(fptr); //gets the next byte to assemble ascii value

	      if(CBLoc != 7)
		{
		  myFlag1 = fsetpos(fptr, &myPrevFPos);

		  if(myFlag1 != 0) // error checking
		    {
		      return NULL;
		    }
		}

	      unsigned char c1 = myByte << (CBLoc + 1);  //gets the first half of the ascii value
	      unsigned char c2 = myNByte >> (7 - CBLoc); //gets the second half of the ascii value

	      myData[arrPos] = '1';
	      arrPos++;
	      myData[arrPos] = (c1 + c2);  //combines the two halves of the ascii value and stores it
	      arrPos++;                    //in the char array myData
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


// This function provides the right mask based on command bit location
unsigned char CBMask(int myPos)
{
  unsigned char myMask = 0x80;
  myMask >>= (myPos % 8);
  return myMask;
}


/* This function creates a new HuffNode and stores the
 * argument value inside the HuffNode
 */
HuffNode * create_Node(int value)
{
  HuffNode * myNode = NULL;
  myNode = malloc(sizeof(HuffNode));
  
  if(myNode == NULL) //error checking
    {
      return NULL;
    }
  
  myNode -> value = value;
  myNode -> left = NULL;   //making a new node means intializing both
  myNode -> right = NULL;  //left and right values to NULL
  
  return myNode;
}


// This function pushes HuffNodes onto our working stack
Stack * stack_Push(Stack * head, HuffNode * myNode)
{
  Stack * myNewHead = NULL;
  myNewHead = malloc(sizeof(Stack));
  if(myNewHead == NULL) //error checking
    {
      return NULL;
    }
  myNewHead -> node = myNode;
  myNewHead -> next = head;
  return myNewHead;
}


/* This function pops a value off of our working stack
 * stores it in the memory location specified by argument
 * myNode, and returns the new head of our working stack,
 * which is the one after the node we just popped off.
 */
Stack * stack_Pop(Stack * head, HuffNode ** myNode)
{
  *myNode = head -> node;
  Stack * myNewHead = head -> next; //gets next value on stack to return
  free(head);
  return myNewHead;
}


/* This function allows us to peek at the value on
 * the top of the stack without modifying the current
 * stack. It is not currently used in this program
 * and is left simply for possible need in future
 * programs
 */
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


/* This function takes an array of chars at memory
 * location specified by argument myData, puts them
 * in a HuffNode then puts the HuffNode into our working
 * stack.  It then creates a HuffTree based on the
 * instructions it encounters in the array of chars.
 */
HuffNode * create_HuffTree(char * myData)
{
  int myFlag1 = 0;  //asserts if the tree is created
  int i = 0;
  Stack * myStack = NULL;

  while(!myFlag1)
    {
      if(myData[i] == CH_ONE) //ascii value of 1 is 49
	{
	  i++;
	  HuffNode * myValue = create_Node(myData[i]);
	  myStack = stack_Push(myStack, myValue);
	  i++;
	}
      else if(myData[i] == CH_ZERO) //ascii value of 0 is 48
	{
	  int myCount = stack_Count(myStack);
	  if(myCount == 1) //if the final tree is on the stack
	    {
	      HuffNode * myTree = myStack -> node;
	      free(myStack);
	      myFlag1 = 1;
	      return myTree;
	    }
	  else if(myCount > 1) //otherwise create parent node for top two stack entries
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
	      return NULL; //if we have 0 entries on the stack when faced with a zero we dun goofed
	    }
	  i++;
	}
      else
	{
	  return NULL; //if we go through the char array correctly we should only ever read
	}              //CH_ONE or CH_ZERO at this stage, so if we don't, we messed up.
    }

  return NULL; //we return NULL if myFlag1 is asserted, meaning there has been an error

}


/* This function takes the finalized HuffTree we
 * created in function create_HuffTree and a pointer
 * to an empty file to be written to, and traverses
 * the HuffTree in a post-order fashion, printing 
 * the direction it takes and the values on the leaves
 * it encounters along the way.
 */
void Huff_postOrderPrint(HuffNode *tree, FILE * fptr)
{
  // Base case: empty subtree
  if (tree == NULL) {
    return;
  }

  // Recursive case: post-order traversal

  // Visit left
  fprintf(fptr, "%s", "Left\n");
  Huff_postOrderPrint(tree->left, fptr);
  fprintf(fptr, "%s", "Back\n");
  // Visit right
  fprintf(fptr, "%s", "Right\n");
  Huff_postOrderPrint(tree->right, fptr);
  fprintf(fptr, "%s", "Back\n");
  // Visit node itself (only if leaf)
  if (tree->left == NULL && tree->right == NULL) {
    fprintf(fptr, "%s%c%c", "Leaf: ", tree->value, '\n');
  }
    
}


/* This function helps destroy the HuffTree when we
 * are done printing the finalized HuffTree to the 
 * output file.  It destroys the HuffTree in a post-order
 * fashion recursively.
 */
void destroy_helper(HuffNode * array)
{
  if(array -> left != NULL) //checks to see if it has any left children
    {
      destroy_helper(array -> left);
    }
  if(array -> right != NULL) //checks to see if it has any right children
    {
      destroy_helper(array -> right);
    }

  free(array); //destroys itself

  return;
}

/* This function is the main function that destroys the
 * HuffTree we created by checking to ensure there is
 * a HuffNode Tree to destroy, then calling its helper
 * recursive function to actually go throughout the tree
 * and destroy all the nodes on it.
 */
void HuffTree_destroy (HuffNode * array)
{
  if(array != NULL)
    {
      destroy_helper(array);
    }
}
