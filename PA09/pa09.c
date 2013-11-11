

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

  //opening the input file
  FILE * fptr = NULL;
  fptr = fopen(argv[1], "rb");

  if (fptr == NULL) //error checking
    {
      printf("File error!\n");
      return EXIT_FAILURE;
    }

  myData = read_File(fptr, argv[1]); //read the input file to myData

  fclose(fptr); //close the input file

  FILE * myOut = NULL;
  myOut = fopen(argv[2], "w"); //open and clear or create file to store output

  if (myOut == NULL) //error checking
    {
      printf("File error!\n");
      return EXIT_FAILURE;
    }

  HuffNode * myTree = create_HuffTree(myData); //create and store HuffTree from myData

  Huff_postOrderPrint(myTree, myOut); //print the post-order traversal to file pointed
                                      //to by myOut
  HuffTree_destroy(myTree);  //destroy myTree because we're done with it

  free(myData);  //frees the char array because we're done with it

  fclose(myOut);  //closes the output file because it's been written

  return EXIT_SUCCESS;
}

