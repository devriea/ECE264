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

HuffNode * createa_Node(int value)
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
