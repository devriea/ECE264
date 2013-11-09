#include <stdio.h>
#include <stdlib.h>
#include "pa09.h"

unsigned char * read_File(FILE * fptr, int * myLength)
{
int myArrSize = 0;
unsigned char c;
 int i = 0;

 while(fscanf(fptr, "%c", &c) != EOF)
   {
     myArrSize++;
   }
  
 unsigned char * myData = malloc(myArrSize * sizeof(unsigned char));
  
 if(myData == NULL)
   {
     return NULL;
   }

 fseek(fptr, 0, SEEK_SET);
  

 while(fscanf(fptr, "%c", &c) != EOF)
   {
     myData[i] = c;
     i++;
   }

 *myLength = i + 1;

 return myData;
}

char * convert_Bin(unsigned char * myData)
{
  unsigned char c = myData[0];
  
  printf("%d ", c);
  
  c >>= 1;
  
  printf("%d ", c);

  return NULL;

}
