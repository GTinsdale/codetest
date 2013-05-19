/*
 * Blazing Griffin code test
 * Part 1 : Palindromes
 *
 * Trevor Fountain
 * April 2013
 */

#include <stdio.h>

//Use the string library
#include <string.h>

bool isPalindrome(const char *string)
{
  // Implement me!
  //get the length of the string and adjust for 0 start
  int l=strlen(string)-1;

  //loop through the string and compare the characters
  for(int i=0; i<=l; i++)
    {
      //compare the 
      if(string[i]!=string[l])
	{
	  return false;
	}
      //decrement l
      l--;
    }

  //if we got through the loop we must have a good palindrome so return true
  return true;
}

int main(int argc, char **argv)
{
  bool pass = 
    isPalindrome("racecar") &&
    !isPalindrome("notapalindrome") &&
    isPalindrome("aaaaAAAAaaaa") &&
    !isPalindrome("((((())))))") &&
    isPalindrome("FOO OOF");

  printf("%s\n", pass ? "PASS" : "FAIL");

  return 0;
}
