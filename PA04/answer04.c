/*
 * Please fill the functions in this file.
 * You can add additional functions. 
 *
 * Hint: 
 * You can write additonal functions.
 * You can test your functions with your own input file.
 * See details in README or typing command ./pa04 in terminal after make.
 * See output format examples in any of the files in directory expected.
 * 
 * You may create additional arrays if needed.  The maximum size
 * needed is specified by MAXLENGTH in pa04.h.
 */

#include "pa04.h"
#include <stdio.h>
#include <stdlib.h>


/*
 * =================================================================
 * This function prints all partitions of a positive integer value
 * For example, if the value is 3:
 *
 * partitionAll 3
 * = 1 + 1 + 1
 * = 1 + 2
 * = 2 + 1
 * = 3
 */

void printArray(int* arr, int length)
{
  int i = 0;

  printf("= ");

  for(i = 0; i<length-1; i++)
    {
      printf("%d + ", arr[i]);
    }

  printf("%d\n", arr[i]);
}

void partitionHelper(int* arr, int length)
{
  int myLastVal = arr[length-1];
  int i = 0;

  if(length == 1)
    {
      return;
    }

  if(myLastVal == 1)
    {
      arr[length-1] = 0;
      arr[length-2] = arr[length-2] + 1;
      printArray(arr, length-1);
      partitionHelper(arr, length-1);
    }
  else
    {
      arr[length-2] = arr[length-2] + 1;
      myLastVal = myLastVal - 1;
      for(i = 0; i < myLastVal; i++)
	{
	  arr[length - 1 + i] = 1;
	}
      length = length + i - 1;
      printArray(arr, length);
      partitionHelper(arr, length);
    }
}

void partitionAll(int value)
{
  printf("partitionAll %d\n", value);
  int myArr[MAXLENGTH];
  int i = 0;

  for(i = 0; i < value; i++)
    {
      myArr[i] = 1;
    }

  printArray(myArr, i);

  partitionHelper(myArr, i);
  
}
/*
 * =================================================================
 * This function prints the partitions that use increasing values.
 *
 * For example, if value is 5
 * 2 + 3 and
 * 1 + 4 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 3 and
 * 2 + 1 + 2 and
 * 3 + 2 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 *
 */

/*
int sumArray(int* arr, int length)
{
  int i = 0;
  int mySum = 0;

  for(i=0; i<length; i++)
    {
      mySum += arr[i];
    }

  return mySum;
}

*/

void printPartition(int* arr, int length)
{
  int ind;

  printf("= ");

  for (ind = 0; ind < length - 1; ind ++)
    {
      printf("%d + ", arr[ind]);
    }
  printf("%d\n", arr[length - 1]);
}


void partitionIncreasingHelper(int* arr, int ind, int left)
{
  int val;
  if (left == 0)
    {
      printPartition(arr, ind);
      return;
    }
  for(val = 1; val <= left; val++)
    {
      if(((ind > 0) && (val > arr[ind-1])) || (ind == 0))
	{
	  arr[ind] = val;
	  partitionIncreasingHelper(arr, ind + 1, left - val);
	}
    }
}

void partitionIncreasing(int value)
{
  printf("partitionIncreasing %d\n", value);

  int myArr[MAXLENGTH];

  partitionIncreasingHelper(myArr, 0, value);

}

/*
 * =================================================================
 * This function prints the partitions that use Decreasing values.
 *
 * For example, if value is 5
 * 3 + 2 and
 * 4 + 1 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 3 and
 * 2 + 1 + 2 and
 * 2 + 3 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 *
 */

void partitionDecreasingHelper(int* arr, int ind, int left)
{
  int val;
  if (left == 0)
    {
      printPartition(arr, ind);
      return;
    }
  for(val = left; val >= 1; val--)
    {
      if(((ind > 0) && (val < arr[ind-1])) || (ind == 0))
	{
	  arr[ind] = val;
	  partitionDecreasingHelper(arr, ind + 1, left - val);
	}
    }
}

void partitionDecreasing(int value)
{
  printf("partitionDecreasing %d\n", value);
  
  int myArr[MAXLENGTH];

  partitionDecreasingHelper(myArr, 0, value);

}

/*
 * =================================================================
 * This function prints odd number only partitions of a positive integer value
 * For example, if value is 5
 * 1 + 1 + 1 + 1 + 1 and
 * 1 + 3 + 1 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 1 + 2 and
 * 2 + 1 + 2 and
 * 2 + 3 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */

void partitionOddHelper(int* arr, int ind, int left)
{
  int val;
  if (left == 0)
    {
      printPartition(arr, ind);
      return;
    }
  for(val = 1; val <= left; val++)
    {
      if(val % 2 == 1)
	{
	  arr[ind] = val;
	  partitionOddHelper(arr, ind + 1, left - val);
	}
    }
}


void partitionOdd(int value)
{
  printf("partitionOdd %d\n", value);

  int myArr[MAXLENGTH];

  partitionOddHelper(myArr, 0, value);
}

/*
 * =================================================================
 * This function prints even number only partitions of a positive integer value
 * For example, if value is 8
 * 2 + 2 + 2 + 2and
 * 2 + 4 + 2 are valid partitions
 *
 * 8 is a valid partition
 *
 * 2 + 1 + 1 + 2 + 2and
 * 2 + 1 + 2 + 3and
 * 5 + 3 are invalid partitions.
 *
 * if the value is 5, there will be no result generated
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */

void partitionEvenHelper(int* arr, int ind, int left)
{
  int val;
  if (left == 0)
    {
      printPartition(arr, ind);
      return;
    }
  for(val = 1; val <= left; val++)
    {
      if(val % 2 == 0)
	{
	  arr[ind] = val;
	  partitionEvenHelper(arr, ind + 1, left - val);
	}
    }
}

void partitionEven(int value)
{
  printf("partitionEven %d\n", value);

  int myArr[MAXLENGTH];

  partitionEvenHelper(myArr, 0, value);

}

/*
 * =================================================================
 * This function prints alternate ood and even number partitions of a positive integer value. Each partition starts from and odd number, even number, odd number again, even number again...etc.
 *
 * For example, if value is 6
 * 1 + 2 + 1 + 2 and
 * 3 + 2 + 1 are valid partitions
 *
 * 6 is not a valid partition
 *
 * 2 + 1 + 1 + 2 and
 * 2 + 1 + 3and
 * 5 + 1 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */

void partitionOddAndEvenHelper(int* arr, int ind, int left, int myFlag)
{
  int val;
  if (left == 0)
    {
      printPartition(arr, ind);
      return;
    }
  for(val = 1; val <= left; val++)
    {
      if(((myFlag == 1) && (val % 2 == 1)) || ((myFlag == 0) && (val % 2 == 0)))
	{
	  arr[ind] = val;
	  partitionOddAndEvenHelper(arr, ind + 1, left - val, abs(myFlag - 1));
	}
    }
}

void partitionOddAndEven(int value)
{
  printf("partitionOddAndEven %d\n", value);

  int myArr[MAXLENGTH];

  partitionOddAndEvenHelper(myArr, 0, value, 1);
  
}

/*
 * =================================================================
 * This function prints prime number only partitions of a positive integer value
 * For example, if value is 6
 * 2 + 2 + 2 and
 * 3 + 3 are valid partitions
 *
 * 6 is not a valid partition
 * 
 * 2 + 4 and
 * 1 + 5 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */

int isPrime(int value)
{
  if(value <= 1)
    {
      return 0;
    }

  int i = 0;
  
  for(i = 2; i*2 <= value; i++)
    {
      if(value % i == 0)
	{
	  return 0;
	}
    }
  return 1;
}

void partitionPrimeHelper(int* arr, int ind, int left)
{
  int val;
  if (left == 0)
    {
      printPartition(arr, ind);
      return;
    }
  for(val = 1; val <= left; val++)
    {
      if(isPrime(val))
	{
	  arr[ind] = val;
	  partitionPrimeHelper(arr, ind + 1, left - val);
	}
    }
}


void partitionPrime(int value)
{
  printf("partitionPrime %d\n", value);

  int myArr[MAXLENGTH];

  partitionPrimeHelper(myArr, 0, value);
}
