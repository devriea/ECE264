

#include <stdio.h>
#include <stdlib.h>
#include "pa09.h"

int main ( int argc , char ** argv )
{
  if(argc != 3)
    {
      printf("usage: ./pa09 <input file> <output file>\n");
      return EXIT_FAILURE;
    }

  char * myData;

  //reading input file
  FILE * fptr = NULL;
  fptr = fopen(argv[1], "rb");

  if (fptr == NULL)
    {
      printf("File error!\n");
      return EXIT_FAILURE;
    }

  myData = read_File(fptr);

  fclose(fptr);

  FILE * myOut = NULL;
  myOut = fopen(argv[2], "w");

  if (myOut == NULL)
    {
      printf("File error!\n");
      return EXIT_FAILURE;
    }

  HuffNode * myTree = create_HuffTree(myData);

  Huff_postOrderPrint(myTree, myOut);

  HuffTree_destroy(myTree);

  free(myData);

  fclose(myOut);

  return EXIT_SUCCESS;
}

