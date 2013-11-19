
#include "pa10.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

#define TRUE 1
#define FALSE 0
#define MAX_LENGTH 12

void printUsage(char * argv0)
{
    printf("\n"
	   "   Usage: %s <cmd> <arg>\n"
	   "\n"
	   "      <cmd> can be one of 'sort', 'sortable',\n"
	   "      or 'shapes'.\n"
	   "\n"
	   "      If <cmd> is 'sort' or 'sortable', then\n"
	   "      <arg> must be a unique sequence of\n"
	   "      digits from [0-9]. 'sort' will sort them,\n"
	   "      and 'sortable' will print 'Y' or 'N'\n"
	   "      depending on whether they are stack-\n"
	   "      sortable.\n"
	   "\n"
	   "      If <cmd> is 'shapes', then <arg> must be\n"
	   "      a digit from [1..9] inclusive, and will\n"
	   "      print all the _unique_ shapes of binary\n"
	   "      trees with that many nodes.\n"
	   "\n"
	   , basename(argv0));
}

int charcmp(const void * a, const void * b)
{
    return *((char*)a) - *((char*)b);
}

int checkArrayStr(const char * str)
{
    int len = strlen(str);
    if(len == 0)
	return FALSE;

    int ret = TRUE;
    char * cpy = strdup(str);
    qsort(cpy, len, sizeof(char), charcmp);

    if(cpy[0] < '0' || cpy[len-1] > '9')
	ret = FALSE;

    // Now just check for duplicates...
    int i;
    for(i = 1; i < len && ret; ++i)
	if(cpy[i] == cpy[i-1])
	    ret = FALSE;

    free(cpy);
    return ret;
}

char * * readInput(char * filename, int * length)
{
  FILE * fptr = fopen(filename, "r");
  if(fptr == NULL)
    {
      printf("File error!\n");
      return NULL;
    }
  
  char lenBuffer[MAX_LENGTH];
  int myLen = 0;

  while(fgets(lenBuffer, MAX_LENGTH, fptr) != NULL)
  {
    myLen++;
  }

  fseek(fptr, 0, SEEK_SET);

  char * myTemp = NULL;

  char * * myData = malloc(sizeof(myTemp) * myLen);

  int i = 0;

  for(i = 0; i < myLen; i++)
  {
    myData[i] = malloc(sizeof(char) * MAX_LENGTH);
  }

  i = 0;

  while(i < myLen)
  {
    fgets(myData[i], MAX_LENGTH, fptr);
    
    i++;
  }

  fclose(fptr);

  *length = myLen;

  return myData;

}
  

void sortOutput(char * array, FILE * fptr)
{
  int len = strlen(array) - 1;
  int * myArray = malloc(sizeof(int) * len);
  int i = 0;
  for(i = 0; i < len; ++i)
  {
    myArray[i] = array[i] - '0';
  }
  
  fprintf(fptr, "input: ");
  
  for(i = 0; i < len; i++)
  {
    fprintf(fptr, "%d", myArray[i]);
  }
  
  fprintf(fptr, "\n");

  stackSort(myArray, len);

  fprintf(fptr, "output: ");

  for(i = 0; i < len; i++)
  {
    fprintf(fptr, "%d", myArray[i]);
  }

  free(myArray);

  fprintf(fptr, "\n\n");

}

void isSortableOutput(char * array, FILE * fptr)
{
  int len = strlen(array) - 1;
  int * myArray = malloc(sizeof(int) * len);
  int i = 0;
  for(i = 0; i < len; ++i)
  {
    myArray[i] = array[i] - '0';
  }
  
  fprintf(fptr, "input: ");
  
  for(i = 0; i < len; i++)
  {
    fprintf(fptr, "%d", myArray[i]);
  }
  
  fprintf(fptr, "\n");

  int myAns = isStackSortable(myArray, len);

  fprintf(fptr, "output: %d", myAns);

  free(myArray);

  fprintf(fptr, "\n\n");
}
  

int main(int argc, char * * argv)
{
    if(argc != 4) 
	{
	    printUsage(argv[0]);
	    return EXIT_FAILURE;
	}

    int ret = EXIT_SUCCESS;
    const char * cmd = argv[1];
    int * array = NULL;
    int len = 0;
    int myLength = 0;
    int i;




    /*if(strcmp(cmd, "sort") == 0 || strcmp(cmd, "sortable") == 0) 
	{
	    const char * arrstr = argv[2];
	    if(!checkArrayStr(arrstr)) 
		{
		    fprintf(stderr, "Invalid array, aborting\n");
		    return EXIT_FAILURE;
		}
	    len = strlen(arrstr);
	    array = malloc(sizeof(int) * len);
	    for(i = 0; i < len; ++i) 
		array[i] = arrstr[i] - '0';
	}*/




    if(strcmp(cmd, "sort") == 0) 
      {
	char * * myData = readInput(argv[2], &myLength);
	FILE * fptr = fopen(argv[3], "w");

	for(i = 0; i < myLength; i++)
	  {
	    sortOutput(myData[i], fptr);
	    free(myData[i]);
	  }

	fclose(fptr);
	free(myData);
      } 
    else if(strcmp(cmd, "sortable") == 0) 
	{
	  char * * myData = readInput(argv[2], &myLength);
	  FILE * fptr = fopen(argv[3], "w");

	  for(i = 0; i < myLength; i++)
	    {
	      isSortableOutput(myData[i], fptr);
	      free(myData[i]);
	    }

	  fclose(fptr);
	  free(myData);
	}
    else if(strcmp(cmd, "shapes") == 0) 
	{
	    len = atoi(argv[2]);
	    if(len < 1 || len > 9) 
		{
		    fprintf(stderr, "Invalid number of shapes... "
			    "aborting\n");
		    ret = EXIT_FAILURE;
		} 
	    else 
		{
		    genShapes(len);
		}
	}
    else 
	{
	    fprintf(stderr, "Invalid command: '%s', aborting\n", cmd);
	}

    free(array);

    return ret;
}

