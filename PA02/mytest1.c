#include <stdio.h>


int main()
{
  char foo[10] = "foo";
  
  printf("%s \n \n", foo);

  my_strinsert(foo, "bar", 0);
  
  printf("%s \n",foo);


  return 0;
}


/**
 * Insert a null-terminated string s2 in the null-terminated string s1
 * at position pos.  All characters following position pos in s1 will
 * be moved to follow directly after the inserted characters from s2;
 * no characters will be overwritten.  Note: you can assume that there
 * is sufficient memory available in s1.
 * 
 * Hint: there is no need to create any temporary memory; simply copy
 * the contents of the string after position pos to its new location
 * starting from the back of the string and going forwards.
 * 
 * Insertions should happen BEFORE the character position referenced
 * by pos.  In other words, inserting s2 at position 0 (the first
 * character of a string) in s1 is equivalent to the string s2
 * followed by string s1.
 * 
 * If the character position pos is higher (or equivalent to) the
 * length of string s1, s2 will simply be appended to the end of s1
 * (i.e. it is equivalent to my_strcat(s1, s2);
 * 
 * Example: char foo[10] = "foo";
 * my_strinsert(foo, "bar", 0) yields "barfoo".
 * 
 * Example(2): char foo[10] = "foo";
 * my_strinsert(foo, "bar", 100) yields "foobar".
 */
void my_strinsert(char *s1, const char *s2, int pos)
{
  int myLen = 0;
  int myLen2 = 0;
  int i = 0;
  int j = 0;

  while(s1[myLen] != '\0')
  {
    myLen++;
  }

  while(s2[myLen2] != '\0')
  {
    myLen2++;
  }

  for(i = pos; (i-pos) < myLen2; i++)
  {
    s1[i + myLen2] = s1[i];
    s1[i] = s2[i-pos];
  }

  s1[myLen+myLen2+1] = '\0';

  
  if(pos >= myLen)
  {
    for(i = myLen; s2[j] != '\0'; i++)
    {
      s1[i] = s2[j];
      j++;
    }

    s1[i+1] = '\0';

    return;
  }
}
