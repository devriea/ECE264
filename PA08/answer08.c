#include "pa08.h"
#include <stdio.h>
#include <stdlib.h>

/* 
 * Create a single instance of a sparse array tree node with a specific
 * index and value. This Sparse array will be implemented by a binary tree.
 *
 * Arguments:
 * index         the index to be stored in the node
 * value         the value to be stored in the node
 * 
 * returns:
 * SparseNode *  the pointer points to the node just constructed
 *
 * This is a constructor function that allocates
 * memory for a sparse array tree node, and it copies the integer values, and sets the 
 * subtree pointers to NULL. 
 */

SparseNode *SparseNode_create(int index, int value)
{
  SparseNode * myNode = NULL;
  myNode = malloc(sizeof(SparseNode));
  myNode -> index = index;
  myNode -> value = value;
  myNode -> left = NULL;
  myNode -> right = NULL;
  return myNode;
}

/* Add a particular value into a sparse array tree on a particular index.
 *
 * Arguments:
 * *array        the root node of the sparse array tree
 * index         the index to be stored in the node
 * value         the value to be stored in the node
 * 
 * returns:
 * SparseNode *  the pointer points to the root node of the modified sparse 
 *               array tree
 *
 * The sparse array tree uses the index as a key in a binary search tree.
 * If the index does not exist, create it. 
 * If the index exists, REPLACE the value to the new one. Use the index to
 * determine whether to go left or right in the tree (smaller index
 * values than the current one go left, larger ones go right).
 */

SparseNode * SparseArray_insert ( SparseNode * array, int index, int value )
{
  if(array == NULL)
    {
      array = SparseNode_create(index, value);
    }
  else if(array -> index == index)
    {
      array -> value = value;
    }
  else if(array -> index > index)
    {
      if(array -> left == NULL)
	{
	  array -> left = SparseNode_create(index, value);
	}
      else
	{
	  SparseArray_insert(array -> left, index, value);
	}
    }
  else if(array -> index < index)
    {
      if(array -> right == NULL)
	{
	  array -> right = SparseNode_create(index, value);
	}
      else
	{
	  SparseArray_insert(array -> right, index, value);
	}
    }
  else
    {
      return NULL;
    }
  
  return array;

}

/* Build a sparse array tree from given indices and values with specific length.
 *
 * Arguments:
 * index*         a pointer points to the start position of the index array
 * value*         a pointer points to the start position of the value array
 * length         the size of both array
 * 
 * returns:
 * SparseNode *   the pointer points to the root node of sparse array tree
 *                just constructed
 *
 * It returns a sparse array tree. 
 * You need to insert tree nodes in order
 *
 * (the first sparse array node contains indices[0] and values[0], second node
 * contains indices[1] and values[1]. Basically, each tree node is constructed
 * with each pair in indices and values array. In other words, elements of 
 * indices and values with the same index should go into the same node.)
 */

SparseNode *SparseArray_build(int * indicies, int * values, int length)
{
  int i = 0;
  SparseNode * myNode = NULL;

  for(i = 0; i < length; i++)
    {
      myNode = SparseArray_insert(myNode, indicies[i], values[i]);
    }
  
  return myNode;
}

/* Destroy an entire sparse array tree. 
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * 
 * returns:
 * void
 *
 * traversing the binary tree in postorder. Use the
 * SparseNode_destroy () function to destroy each node by itself.
 */
void SparseNode_destroy( SparseNode * array)
{
  free(array);
}

void destroy_helper(SparseNode * array)
{
  if(array -> left != NULL)
    {
      destroy_helper(array -> left);
    }
  if(array -> right != NULL)
    {
      destroy_helper(array -> right);
    }

  SparseNode_destroy(array);

  return;
}

void SparseArray_destroy ( SparseNode * array )
{
  if(array != NULL)
    {
      destroy_helper(array);
    }
}

/* Retrieve the smallest index in the sparse array tree.
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * 
 * returns:
 * int            the smallest index in the sparse array tree
 *
 * (Hint: consider the property of binary search tree) 
 */
int SparseArray_getMin ( SparseNode * array )
{
  if(array == NULL)
    {
      return -1;
    }
  else if(array -> left == NULL)
    {
      return array -> index;
    }
  else
    {
      return SparseArray_getMin(array -> left);
    }
}

/* Retrieve the largest index in the sparse array tree. 
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * 
 * returns:
 * int            the largest index in the sparse array tree
 *
 * (Hint: consider the property of binary search tree) 
 */
int SparseArray_getMax ( SparseNode * array )
{

  if(array == NULL)
    {
      return -1;
    }
  else if(array -> right == NULL)
    {
      return array -> index;
    }
  else
    {
      return SparseArray_getMax(array -> right);
    }
}


/* Retrieve the node associated with a specific index in a sparse
 * array tree.  
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * index          the index of the node you want to search
 * 
 * returns:
 * SparseNode*    the node with the index that you searched from the tree.
 *                If no node found, NULL should be returned. 
 *                
 * Hint: If the given index is smaller than the current
 * node, search left ; if it is larger, search right.
 */
SparseNode * SparseArray_getNode(SparseNode * array, int index )
{
  if(array == NULL)
    {
      return NULL;
    }
  else if(array -> index == index)
    {
      return array;
    }
  else if(array -> index > index)
    {
      if(array -> left == NULL)
	{
	  return NULL;
	}
      else
	{
	  return SparseArray_getNode(array -> left, index);
	}
    }
  else if(array -> index < index)
    {
      if(array -> right == NULL)
	{
	  return NULL;
	}
      else
	{
	  return SparseArray_getNode(array -> right, index);
	}
    }
  else
    {
      return NULL;
    }

}

/* Remove a value associated with a particular index from the sparse
 * array. It returns the new
 * sparse array tree ( binary tree root ). 
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * index          the index of the node you want to remove
 * 
 * returns:
 * SparseNode*    the root node of the sparse array tree that you just modified
 *          
 *    
 * HINT : First, you need to find that node. Then, you will need to isolate
 * several different cases here :
 * - If the array is empty ( NULL ), return NULL
 * - Go left or right if the current node index is different.

 * - If both subtrees are empty, you can just remove the node.

 * - If one subtree is empty, you can just remove the current and
 * replace it with the non - empty child.

 * - If both children exist, you must find the immediate successor of
 * the current node ( leftmost of right branch ), swap its values with
 * the current node ( BOTH index and value ), and then delete the
 * index in the right subtree.
 */
SparseNode * SparseArray_remove ( SparseNode * array, int index )
{
  if(array == NULL)
    {
      return NULL;
    }
  else if(array -> index == index)
    {
      if((array -> right == NULL) && (array -> left == NULL))
	{
	  free(array);
	  return NULL;
	}
      else if((array -> right == NULL) && (array -> left != NULL))
	{
	  SparseNode * myTemp = NULL;
	  myTemp = array -> left;
	  free(array);
	  return myTemp;
	}
      else if((array -> right != NULL) && (array -> left == NULL))
	{
	  SparseNode * myTemp = NULL;
	  myTemp = array -> right;
	  free(array);
	  return myTemp;
	}
      else if((array -> right != NULL) && (array -> left != NULL))
	{
	  SparseNode * myTemp = NULL;
	  int tValue = 0;
	  int tIndex = 0;
	  myTemp = array -> right;
	  while(myTemp -> left != NULL)
	    {
	      myTemp = myTemp -> left;
	    }
	  tValue = array -> value;
	  tIndex = array -> index;
	  array -> value = myTemp -> value;
	  array -> index = myTemp -> index;
	  myTemp -> value = tValue;
	  myTemp -> index = tIndex;
	  array -> right = SparseArray_remove(array -> right, index);
	  return array;
	}
    }
  else if(array -> index > index)
    {
      array -> left = SparseArray_remove(array -> left, index);
    }
  else if(array -> index < index)
    {
      array -> right = SparseArray_remove(array -> right, index);
    }

  return NULL;
}

/* The function makes a copy of the input sparse array tree
 * and it returns a new copy. 
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * 
 * returns:
 * SparseNode*    the root node of the new sparse array tree that you just
 *                copied from the input sparse array tree.
 *       
 */
SparseNode * copyNodeHelper(SparseNode * array)
{
  if(array == NULL)
    {
      return NULL;
    }

  SparseNode * myTemp = SparseNode_create(array -> index, array -> value);
  myTemp -> left = array -> left;
  myTemp -> right = array -> right;

  return myTemp;
}

SparseNode * copyArrayHelper(SparseNode * array)
{
  if(array == NULL)
    {
      return NULL;
    }
  else
    {
      SparseNode * myTemp = copyNodeHelper(array);
      myTemp -> left = copyArrayHelper(myTemp -> left);
      myTemp -> right = copyArrayHelper(myTemp -> right);
      
      return myTemp;
    }
}

SparseNode * SparseArray_copy(SparseNode * array)
{
  SparseNode * myCopy = copyArrayHelper(array);
  
  return myCopy;
}

/* Merge array_1 and array_2, and return the result array. 
 * This function WILL NOT CHANGE the contents in array_1 and array_2.
 *
 * Arguments:
 * *array_1         the root node of the first sparse array tree
 * *array_2         the root node of the second sparse array tree
 * 
 * returns:
 * SparseNode*    the root node of the new sparse array tree that you just
 *                merged from the two input sparse array tree
 *     
 * When merging two sparse array tree:
 * 1. The contents in array_1 and array_2 should not be changed. You should make
 *    a copy of array_1, and do merging in this copy.
 * 2. array_2 will be merged to array_1. This means you need to read nodes in 
 *    array_2 and insert them into array_1.
 * 3. You need to use POST-ORDER to traverse the array_2 tree. 
 * 4. Values of two nodes need to be added only when the indices are the same.
 * 5. A node with value of 0 should be removed.
 * 6. if array_2 has nodes with index different than any nodes in array_1, you
 *    should insert those nodes into array_1.
 * 
 * Hint: you may write new functions
 */
SparseNode * myMerge_helper(SparseNode * array, int index, int value)
{
  if(array == NULL)
    {
      return SparseNode_create(index, value);
    }
  if(array -> index == index)
    {
      array -> value = array -> value + value;
    }
  if(array -> index > index)
    {
     array -> left = myMerge_helper(array -> left, index, value);
    }
  if(array -> index < index)
    {
      array -> right = myMerge_helper(array -> right, index, value);
    }
  
  return array;
}

SparseNode * myMerge_runner(SparseNode * myMerge, SparseNode * array2)
{
  if(array2 -> left != NULL)
    {
      myMerge = myMerge_runner(myMerge, array2 -> left);
    }
  if(array2 -> right != NULL)
    {
      myMerge = myMerge_runner(myMerge, array2 -> right);
    }

  myMerge = myMerge_helper(myMerge, array2 -> index, array2 -> value);

  return myMerge;
}

int count_zeroes(SparseNode * array)
{
  int i = 0;
  if(array -> left != NULL)
    {
      i += count_zeroes(array -> left);
    }
  if(array -> right != NULL)
    {
      i += count_zeroes(array -> right);
    }
  if(array -> value == 0)
    {
      i++;
    }
  return i;
}

void get_zero_ind(SparseNode * array, int * zeroInd, int ind)
{
  if(array -> left != NULL)
    {
      get_zero_ind(array -> left, zeroInd, ind);
    }
  if(array -> right != NULL)
    {
      get_zero_ind(array -> right, zeroInd, ind);
    }
  if(array -> value == 0)
    {
      zeroInd[ind] = array -> index;
      ind++;
    }
}

SparseNode * rem_zeroes(SparseNode * array)
{
  int numZeroes = 0;
  int i = 0;

  numZeroes = count_zeroes(array);

  int * myZeroInd = malloc(sizeof(int) * numZeroes);

  get_zero_ind(array, myZeroInd, 0);

  for(i = 0; i < numZeroes; i++)
    {
      array = SparseArray_remove(array, myZeroInd[i]);
    }
  
  free(myZeroInd);

  return array;
}

SparseNode * SparseArray_merge(SparseNode * array_1, SparseNode * array_2)
{
  SparseNode * myMerge = NULL;

  if(array_1 == NULL)
    {
      if(array_2 == NULL)
	{
	  return NULL;
	}

      myMerge = SparseArray_copy(array_2);
      return myMerge;
    }
  
  myMerge = SparseArray_copy(array_1);

  if(array_2 == NULL)
    {
      return myMerge;
    }

  myMerge = myMerge_runner(myMerge, array_2);

  myMerge = rem_zeroes(myMerge);

  return myMerge;

}
