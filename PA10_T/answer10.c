
#include "pa10.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

/**
 * Returns a pointer to a new empty stack.
 */
Stack * Stack_create()
{
  Stack * myStack = NULL;
  myStack = malloc(sizeof(Stack));
  if(myStack == NULL)
    {
      return NULL;
    }
  myStack -> list = NULL;
  return myStack;
}

/**
 * Frees all memory associated with the stack. 
 * Don't forget that you _must_ free the entire contained linked-list.
 * Also, you must safely do _nothing_ if stack == NULL. 
 */
void Stack_destroy_helper(ListNode * myList)
{
  if(myList == NULL)
    {
      return;
    }
  Stack_destroy_helper(myList -> next);
  free(myList);
}

void Stack_destroy(Stack * stack)
{
  if(stack == NULL)
    {
      return;
    }
  Stack_destroy_helper(stack -> list);
  free(stack);
}

/**
 * Returns TRUE (something other than zero) if the stack is empty.
 */
int Stack_isEmpty(Stack * stack)
{
  if(stack == NULL) //if the stack doesn't exist it should be empty, right?
    {
      return FALSE;
    }
  else if(stack -> list == NULL) //if the stack exists and is empty, return TRUE
    {
      return TRUE;
    }
  else
    {
      return FALSE;
    }
}

/**
 * Pop the front 'value' from the stack.
 *
 * More precisely, this function must do two things:
 * (1) Return the value of the head node of the stack's list
 * (2) Remove the head node of the stack's list, freeing it.
 */
int Stack_pop(Stack * stack)
{
  if(stack == NULL || stack -> list == NULL)
    {
      return -1;
    }

  ListNode * myHead = stack -> list;
  int myValue = myHead -> value;
  stack -> list = myHead -> next;
  free(myHead);
  return myValue;
}

/**
 * Push an 'value' onto the front of the stack.
 *
 * More precisely, this function must:
 * (1) Create a new ListNode with 'value' for it's value.
 * (2) Push that new ListNode onto the front of the stack's list.
 */
void Stack_push(Stack * stack, int value)
{
  if(stack == NULL)
    {
      return;
    }

  ListNode * myNode = NULL;
  myNode = malloc(sizeof(ListNode));

  if(myNode == NULL) //Error checking
    {
      return;
    }

  myNode -> value = value;
  myNode -> next = stack -> list;
  stack -> list = myNode;
}

/**
 * Sort 'array' of length 'len' using Donald Knuth's "StackSort"
 *
 * To do this, you must implement the following pseudo-code:
 * (1) Maintain a 'write_index'. This is where you'll write values to
 *     as you sort them. It starts off as zero.
 * (2) Initialize an empty stack
 * (3) For each input value 'x':
 *     (3.a) While the stack is nonempty and 'x' is larger than the 
 *           front 'value' on the stack, pop 'value' and:
 *           (3.a.i) Write 'value' to array[write_index], and 
 *                   increment write_index.
 *     (3.b) Push x onto the stack.
 * (4) While the stack is nonempty, pop the front 'value' and follow
 *     step (3.a.i).
 *
 * The output should be a sorted array if, and only if, the array
 * is stack-sortable. You can find files full of stack-sortable and
 * stack-unsortable arrays in the 'expected' folder.
 */
int stackPeek(Stack * stack)
{
  if(stack == NULL || stack -> list == NULL)
    {
      return -1;
    }
  return stack -> list -> value;
}

void stackSort(int * array, int len)
{
  if(len == 0)
    {
      return;
    }

  Stack * myStack = Stack_create();
  
  if(myStack == NULL)
    {
      return;
    }
  
  //int myWriteIndex[len + 1];
  
  int i = 0;
  int wIndex = 0;
  Stack_push(myStack, array[i]);
  i++;
  
  while(i < len)
    {
      while((!Stack_isEmpty(myStack)) && (i < len))
	{
	  if(array[i] > stackPeek(myStack))
	    {
	      array[wIndex] = Stack_pop(myStack);
              wIndex++;
	    }
	  else
	    {
	      Stack_push(myStack, array[i]);
              i++;
	    }
	}
      if(Stack_isEmpty(myStack))
	{
	  Stack_push(myStack, array[i]);
          i++;
	}
    }
  
  while(!Stack_isEmpty(myStack))
    {
      array[wIndex] = Stack_pop(myStack);
      wIndex++;
    }

  free(myStack);

}

/**
 * Return TRUE (1) if the 'array' of length 'len' is stack-sortable.
 *
 * To do this you must:
 * (1) If 'len' is less than 3, return TRUE.
 * (2) Find the maximum value in 'array'.
 * (3) Partition array into two parts: left of max, and right of max.
 * (4) The maximum value in left must be smaller than the minimum
 *     value in right. (Otherwise return FALSE.)
 * (5) Return TRUE if both left and right are stack-sortable.
 *
 * The 'expected' directory contains files for all sortable and 
 * unsortable sequences of length len. You must return TRUE for every
 * sequence in the sortable files, and you must return FALSE for every
 * sequence in the unsortable files.
 */
int isStackSortable(int * array, int len)
{
  if((len < 0) || (array == NULL))
    {
      return FALSE;
    }

  if(len < 3)
    {
      return TRUE;
    }

  int myMax = array[0];
  int myMaxInd = 0;
  int myLeftMax = array[0];
  int myLeftMaxInd = 0;
  int myRightMin = 0;
  int myRightMinInd = 0;
  int i = 0;

  for(i = 0; i < len; i++)
    {
      if(myMax < array[i])
	{
	  myMax = array[i];
	  myMaxInd = i;
	}
    }

  myRightMin = array[myMaxInd];
  myRightMinInd = myMaxInd;
  
  for(i = 0; i < myMaxInd; i++)
    {
      if(myLeftMax < array[i])
	{
	  myLeftMax = array[i];
	  myLeftMaxInd = i;
	}
    }
  
  if(myMaxInd == len-1)
    {
      myRightMin = myMax;
    }
  else
    {
      myRightMin = array[myMaxInd + 1];
      myRightMinInd = myMaxInd + 1;
      for(i = myMaxInd + 1; i < len; i++)
	{
	  if(myRightMin > array[i])
	    {
	      myRightMin = array[i];
	      myRightMinInd = i;
	    }
	}
    }

  int myMaxIndT = myMaxInd;

  if(myMaxInd != len - 1)
    {
      myMaxIndT++;
    }

  if((myLeftMax < myRightMin) || (myMaxInd == 0))
    {
      return (isStackSortable(array, myMaxInd) && isStackSortable(&array[myMaxIndT], (len - myMaxInd - 1)));
    }
  else
    {
      return FALSE;
    }
}

/**
 * Generates (and prints) all the unique binary tree shapes of size k
 *
 * To do this, you must:
 * (1) Create an array with the elements [1..k] inclusive.
 * (2) Find all the permutations of this array.
 * (3) In the base-case of your permute function, you must test if the
 *     permutation is "stack-sortable"
 * (4) If the permutation is "stack-sortable", then build a binary
 *     tree, and print it using the "Tree_printShape(...)" function.
 *
 * Your genShapes() function must NOT produce duplicate tree shapes.
 * The correct outputs for sizes [1..9] are in the 'expected' 
 * directory.
 */
TreeNode * TreeNode_create(int value)
{
    TreeNode * node = malloc(sizeof(TreeNode));
    node -> value = value;
    node -> left = NULL;
    node -> right = NULL;
    return node;
}

TreeNode * Tree_insert(TreeNode * node, int value)
{
    if(node == NULL)
	return TreeNode_create(value);
    if(value < node -> value)
	node -> left = Tree_insert(node -> left, value);
    if(value > node -> value)
	node -> right = Tree_insert(node -> right, value);
    // If they're equal, then we have nothing to do...
    return node;
}

TreeNode * Tree_build(int * array, int len)
{
    TreeNode * root = NULL;
    int i;
    for(i = 0; i < len; ++i)
	root = Tree_insert(root, array[i]);
    return root;
}

void Tree_destroy(TreeNode * node)
{
    if(node == NULL)
	return;
    Tree_destroy(node -> left);
    Tree_destroy(node -> right);
    free(node);
}

void Tree_printShapeHelper(TreeNode * node)
{
    if(node == NULL)
	return;
    if(node -> left != NULL) {
	printf("(");
	Tree_printShapeHelper(node -> left);
	printf(")");
    }
    printf("%d", node -> value);
    if(node -> right != NULL) {
	printf("(");
	Tree_printShapeHelper(node -> right);
	printf(")");
    }
}

/**
 * This function is given to you:
 */
void Tree_printShape(TreeNode * node)
{
    Tree_printShapeHelper(node);
    printf("\n");
}

void swap(int * array, int i, int j)
{
  int temp = array[i];
  array[i] = array[j];
  array[j] = temp;
}

void permutate(int * array, int myInd, int len)
{
  if(myInd == len)
    {
      if(isStackSortable(array, len))
	{
	  TreeNode * myTree = Tree_build(array, len);
	  Tree_printShape(myTree);
	  Tree_destroy(myTree);
	} 
      return;
    }

  int i = 0;

  for(i = myInd; i < len; i++)
    {
      swap(array, myInd, i);
      permutate(array, myInd + 1, len);
      swap(array, myInd, i);
    }
}
void genShapes(int k)
{
  if(k < 1)
    {
      return;
    }
  
  int i = 0;
  int myArray[k];

  for(i = 0; i < k; i++)
    {
      myArray[i] = i;
    }

  permutate(myArray, 0, k);

  return;
}
