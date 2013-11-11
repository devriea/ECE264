

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

  int i = 0;

  printf("\n");

  while(myData[i] != EOF)
    {
      printf("%c ", myData[i]);
      i++;
    }

  printf("%c", myData[i]);

  printf("\n");

  HuffNode * myTree = create_HuffTree(myData);

  printf("\n");

  //Huff_postOrderPrint(myTree);

  HuffTree_destroy(myTree);

  free(myData);

  return EXIT_SUCCESS;
}

