#include "pa07.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Prints a linked-list "head" into the output file "out"
 *
 * NOTE: we have given the code for this function
 */
void List_print(FILE * out, Node * head)
{
 while(head != NULL)
	{
	    fprintf(out, "%5d: %6d\n", head -> index, head -> value);
	    head = head -> next;
	}
    printf("\n");
}


/**
 * Please fill in the code below
 */

/**
 * Destroys a linked list.
 * Arguments:
 * head    A pointer pointing to the first element of the linked list.
 *
 * Returns:
 * void
 *
 * Destroys (frees memory for) the whole linked list. 
 * You can either use recursion or a while loop.
 */
void List_destroy(Node * head)
{
  if(head == NULL)
  {
    return;
  }

  Node * temp_head;
  temp_head = head;

  Node * del_next;
  del_next = temp_head -> next;

  while(del_next != NULL)
  {
    temp_head -> next = del_next -> next;
  
    free(del_next);

    del_next = temp_head -> next;
  }

  free(temp_head);

}

/**
 * Create and initialize a linked list. 
 *
 * Arguments:
 * value     The "value" of the new node
 * index     The "index" of the new node
 *
 * Returns:
 * Returns a newly constructed node. The node can be the head of a
 * linked list.
 * 
 * You should allocate memory in this function. 
 */
Node * List_create(int value, int index)
{
  Node * head = NULL;
  head = malloc(sizeof(Node));
  head -> next = NULL;
  head -> value = value;
  head -> index = index;

  return head;
}

/**
 * Build a sparse array from the given indices and values with 
 * specific length.
 *
 * Arguments:
 * value    Array of values
 * index    Array of indices
 * length   Length of the above arrays
 *
 * Returns:
 * A sparse array.
 *
 * If a sparse array node has { value = 1000, index = 2 }, then that means that
 * the index "2" caries the value "1000". This is meant to convey an array of 1000 
 * "2s", but instead of creating 1000 nodes in your linked list, you only create
 * 1 node, and that note conceptually has 1000 "copies" of it. Hence 
 * each node in a sparse array has a "value" in addition to its "index".
 *
 * Note that an index can never carry the value of "0", because this would not make
 * any sense; however, negative values are fine. A negative value may seem odd
 * at first blush; however, this is like substraction, and makes sense for certain
 * cases.
 *
 * You need to insert nodes in ascending order by index.
 * See the notes to "List_insert_ascend"
 */

void findNextIndex (int * value, int * index, int length, int * prevIndex, int * prevValue)
{
  int i = 0;
  int myNextIndex = 0;
  int myNextValue = value[0];
  
  for(i = 0; i < length; i++)
  {
    if((index[i] < *prevIndex) && (index[i] > myNextIndex))
    {
      myNextIndex = index[i];
      myNextValue = value[i];
    }
  }

  *prevIndex = myNextIndex;
  *prevValue = myNextValue;

}

int array_Consolidation(int * value, int * index, int length)
{
  int i = 0;
  int j = 0;
  int myNewLength = length;

  for(i = 0; i < length; i++)
  {
    for(j = 0; j < length; j++)
    {
      if((i != j) && (index[j] == index[i]))
      {
        myNewLength--;

        if(i < j)
        {
          value[i] = value[i] + value[j];
          index[j] = -1;
          value[j] = 0;
        }
        else
        {
          value[j] = value[i] + value[j];
          index[i] = -1;
          value[i] = 0;
        }
      }
    }
  }

  return myNewLength;

}
  

Node * List_build(int * value, int * index, int length)
{
  int i = 0;
  int myIndex = index[0];
  int myValue = value[0];
  int myLength = 0;
  Node * head = NULL;
  
  if(length == 0)
  {
    return head;
  }

  myLength = array_Consolidation(value, index, length);

  for(i = 0; i < length; i++)
  {
    if(index[i] > myIndex)
    {
      myIndex = index[i];
      myValue = value[i];
    }
  }

  head = List_create(myValue, myIndex);

  if(length > 1)
  {
    for(i = 1; i < myLength; i++)
    {
      findNextIndex(value, index, length, &myIndex, &myValue);
      head = List_insert_ascend(head, myValue, myIndex);
    }
  }

  return head;
 
}


/**
 * Inserting "value" and "index" into the correct location in the 
 * sparse array "head"
 * 
 * Arguments: 
 * head      A pointer pointing to the first element of the linked list.
 * value     The "value" of the value
 * index     The "value" of the index
 *
 * Returns:
 * A sparse array
 *
 * This function inserts the node ["value", "index"] into the sparse
 * array "head", and ensures that the nodes remain in ascending order
 * by their "index".
 *
 * Before and after the call to this function, "head" must be in
 * ASCENDING order by the "index" of each node.
 */
Node * List_insert_ascend(Node * head, int value, int index)
{
  Node * child = NULL;
  child = malloc(sizeof(Node));
  child -> next = head;
  child -> value = value;
  child -> index = index;
  return child;
}


/**
 * This function deletes the node with the passed "index"
 * 
 * Arguments: 
 * head      A pointer pointing to the first element of the sparse array.
 * index     The index to be deleted
 *
 * Returns: 
 * A sparse array with the node removed (the one with index)
 */
Node * List_delete(Node * head, int index)
{
  Node * myNewHead = NULL;
  Node * myDelHead = NULL;
  Node * myTempHead = NULL;

  if(head -> index == index)
  {
    myNewHead = head -> next;
    free(head);
    return myNewHead;
  }

  myTempHead = head;
  
  while(myTempHead -> next -> index != index)
  {
    myTempHead = myTempHead -> next;
  }
  
  myDelHead = myTempHead -> next;
  myTempHead -> next = myDelHead -> next;

  free(myDelHead);

  return head;

}

/**
 * Copy a list
 *
 * Arguments:
 * head      A pointer pointing to the first element of the sparse array
 *
 * Returns:
 * A copy sparse array
 *
 * This function will copy the sparse array that is passed to it. The
 * copy will be made into new memory. 
 *
 * This is useful, for example, when we want to merge
 * two linked lists together. We can make a copy of one of the linked
 * lists, and then merge the second into the copy. In this way the
 * original copy of the list is not "mutated".
 */
Node * List_copy(Node * head)
{
  int i = 0;
  int j = 0;
  Node * myHead = head;

  while(myHead != NULL)
  {
    i++;
    myHead = myHead -> next;
  }

  int * myVals = malloc(sizeof(int) * i);
  int * myInds = malloc(sizeof(int) * i);
  
  myHead = head;
  
  while(myHead != NULL)
  {
    myVals[j] = myHead -> value;
    myInds[j] = myHead -> index;
    j++;
    myHead = myHead -> next;
  }

  myHead = List_build(myVals, myInds, i);

  free(myVals);
  free(myInds);

  return myHead;


  /*
  Node * myHead = NULL;
  myHead  = malloc(sizeof(Node));
  myHead -> value = head -> value;
  myHead -> index = head -> index;
  myHead -> next = NULL;
  head = head -> next;
  while(head != NULL)
  {
    Node * myNextHead = NULL;
    myNextHead = malloc(sizeof(Node));
    myNextHead -> value = head -> value;
    myNextHead -> index = head -> index;
    myNextHead 
  */
}


/**
 * Merged two linked list together
 * 
 * Arguments:
 * head1      A pointer pointing to linked list 1
 * head2      A pointer pointing to linked list 2
 *
 * Returns:
 * A merged sparse array
 *
 * This function will merge two linked lists. Before merging, you 
 * should make a copy of "head1" so that you will still have the 
 * original array while modifying (merging) the second linked list. 
 *
 * Please refer to the README file for detailed instructions on how to
 * merge two lists.
 *
 * This function should not modify either "head1" or "head2". You only
 * need to make a clone of "head1".
 */
Node * List_insert(Node * head1, Node * toBeInserted)
{
  Node * nextTBI = toBeInserted -> next;
  
  toBeInserted -> next = head1 -> next;
  head1 -> next = toBeInserted;
  return nextTBI;
}
 

Node * List_merge(Node * head1, Node * head2)
{
  Node * hat = NULL;
  Node * head_copy = NULL;
  Node * head2_backup = NULL;

  if(head1 != NULL)
  {
    head_copy = List_copy(head1);
    hat = head_copy;
  }
  
  if(head2 != NULL)
  {
    head2_backup = List_copy(head2);
  }

    while((head_copy != NULL) || (head2 != NULL))
    {
      if((head_copy != NULL) && (head2 != NULL))
      {
        if(head_copy -> index > head2 -> index)
        {
          Node * temp1 = head2 -> next;
          head2 -> next = head_copy;
          head_copy = head2;
          head2 = temp1;
          hat = head_copy;
        }
        else if(head_copy -> index < head2 -> index)
        {
          if(head2 -> index >= head_copy -> next -> index)
          {
            head_copy = head_copy -> next;
          }
          else
          {
            head2 = List_insert(head_copy, head2);
          }
        }
        else
        {
          head_copy -> value = head_copy -> value + head2 -> value;
          //head_copy = head_copy -> next;
          if(head_copy -> value == 0)
          {
            if(hat == head_copy)
            {
              head_copy = List_delete(hat, head_copy -> index);
              hat = head_copy;
            }
            else
            {
              head_copy = List_delete(hat, head_copy -> index);
            }
          }
          head2 = head2 -> next;
        }
        if((head_copy != NULL) && (head_copy -> next == NULL))
        {
          if(head_copy -> index == head2 -> index)
          {
            head_copy -> value = head_copy -> value + head2 -> value;
            if(head_copy -> value == 0)
            {
              if(hat == head_copy)
              {
                head_copy = List_delete(hat, head_copy -> index);
                hat = head_copy;
              }
              else
              {
                head_copy = List_delete(hat, head_copy -> index);
              }
            }
          }
          else
          {
            head_copy -> next = head2;
          }
          head2 = head2_backup;
          return hat;
        }
      }
      else if((head_copy != NULL) && (head2 == NULL))
      {
        head2 = head2_backup;
        return hat;
      }
      else if((head_copy == NULL) && (head2 != NULL))
      {
        //printf("\n\n ERROR \n\n");
        hat = List_copy(head2);
        head2 = head2_backup;
        return hat;
      }
    }
  head2 = head2_backup;
  return hat;  
}

