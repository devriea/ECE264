

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

  int myLength = 0;
  unsigned char * myData;

  //reading input file
  FILE * fptr = NULL;
  fptr = fopen(argv[1], "rb");

  if (fptr == NULL)
    {
      printf("File error!\n");
      return EXIT_FAILURE;
    }

  myData = read_File(fptr, &myLength);

  fclose(fptr);

  int i = 0;

  printf("\n");

  while(i < myLength)
    {
      printf("%d ", myData[i]);
      i++;
    }

  printf("\n");

  convert_Bin(myData);

  printf("\n");

  return EXIT_SUCCESS;
}

