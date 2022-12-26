/**
 * Exercise 3 - Fun with Strings
 *
 * Please read the comments below carefully, they describe your task in detail.
 * Any clarifications and corrections will be posted to Piazza so please keep
 * an eye on the forum!
 *
 * Starter code: Mustafa Quraish & Charles Xu, 2022
 */

#include <stdio.h>
// NO additional imports allowed. You *can* make helper functions, and in fact I strongly
// encourage doing so to make your life easier.

// Maximum length of a string
#define MAX_STRING_LEN 1024

//-----------------------------------------------------------------------------

int str_len(char string[MAX_STRING_LEN])
{
  int i = 0;

  while (string[i] != '\0'){
    i = i + 1;
  }
  return i;

}

int is_substring(char str[], char a[])
{
  int True = 1;
  int False = 0;
  int count = 0;
  int i, j;

  for (i = 0; i < str_len(str); i++)
  {
    if (str[i] == a[0])
    {
      count = 1;
      for (j = 1; j < str_len(a); j++)
      {
        if(str[i + j] == a[j])
        {
          count = count + 1;
        }

      }
    }
  }
  if (count == str_len(a))
  {
    return True;
  }
  return False;
}
/*
int find_start_index(char str[], char a[]){

  int index = -1;
  for (int i = 0; str[i] != '\0'; i++){
    index = -1;

    for (int j = 0; a[j] != '\0'; i++){
      if (str[i + j] != a[j]){
        index = -1;
        break;
      }
      index = i;
    }
    if (index != -1){
      break;
    }
  }
  return index;

}*/

int get_start_index(char str[MAX_STRING_LEN], char a[MAX_STRING_LEN]) {
   int i, j, first_occ;
   i = 0, j = 0;
 
   while (str[i] != '\0') {
 
      while (str[i] != a[0] && str[i] != '\0')
         i++;
 
      if (str[i] == '\0')
         return (-1);
 
      first_occ = i;
 
      while (str[i] == a[j] && str[i] != '\0' && a[j] != '\0') {
         i++;
         j++;
      }
 
      if (a[j] == '\0')
         return (first_occ);
      if (str[i] == '\0')
         return (-1);
 
      i = first_occ + 1;
      j = 0;
   }
}

void replaceSubstring(char str[MAX_STRING_LEN], char a[MAX_STRING_LEN], char b[MAX_STRING_LEN])
{

  /*
   * If `a` is a substring of `str`, then the first occurence of `a` in `str`
   * is replaced with `b`.
   *
   * For example:
   *
   *    char str[50] = "Hello World!";
   *    replaceSubstring(str, "llo W", "---");
   *    printf("%s\n", str);
   *
   * should print out "He---orld!"
   *
   * You may assume that `str[]`` has enough space to store the modified string.
   * Remember that all the strings here all null-terminated, and you must
   * also null-terminate the modified string.
   */
  char string1[MAX_STRING_LEN] = "";
  char string2[MAX_STRING_LEN] = "";

  for (int x = 0; x < str_len(str); x++)
  {
    string1[x] = str[x];
    string1[x+1] = '\0';
  }

  int start_index = get_start_index(str, a);
  int end_index_of_b = start_index + str_len(b);
  int end_index_of_a = start_index + str_len(a);
  int i;
  
  for (i = 0; i < str_len(b); i++)
  {
    str[i + start_index] = b[i];
  }



  if (str_len(a) > str_len(b))
  {
    for (int j = 0; j < str_len(str) - end_index_of_b - (str_len(a) - str_len(b)); j++)
    {
      str[end_index_of_b + j] = string1[end_index_of_b + (str_len(a) - str_len(b)) + j];
    }
    str[str_len(string1) - (str_len(a) - str_len(b))] = '\0';
  }
  else if (str_len(a) < str_len(b))
  {
    for (int z = 0; z < (str_len(string1) - (end_index_of_a - 2)); z++)
    {
      str[start_index + str_len(b) + i] = string1[end_index_of_a + i];
      str[start_index + str_len(b) + i + 1] = '\0';
    }
  }

  // Not returning anything. `str` is modified directly.
  // copying contents of string1 into str
  /*
  for (int y = 0; y < str_len(string1); y++)
  {
    str[y] = string1[y];
    str[y + 1] = '\0';
  }*/
  

  if (is_substring(string1, a) == 0){
    for (int g = 0; g < str_len(string2); g++)
    {
      str[g] = string1[g];
      str[g + 1] = '\0';
    }

  }
  printf("%s\n", str);

}

void changeSubstringCase(char str[], char a[])
{
  /**
   * If `a` is a substring of `str`, then change the case (capitalization) of
   * the first occurence of the corresponding substring in `str`. Special
   * characters (' ', '.', ...) do not need to be handled. You should only
   * change the letters.
   *
   * For example:
   *
   *    char str[100] = "This IS a SENTence WITH BAd CAPITalizaTION";
   *    changeSubstringCase(str, "IS a SENTence WI");
   *    printf("%s\n", str);
   *
   * should print out "This is A sentENCE wiTH BAd CAPITalizaTION".
   */
  int start_index = get_start_index(str, a);
  if (is_substring(str, a) == 1)
  {
    for (int i = 0; i < str_len(a); i++)
    {
      if (str[i + start_index] >= 'a' && str[i + start_index] <= 'z' )
      {
        str[i + start_index] = str[i + start_index] - 32;
      }
      else if (str[i + start_index] >= 'A' && str[i + start_index] <= 'Z')
      {
        str[i + start_index] = str[i + start_index] + 32;
      }
    }
  }
  printf("%s\n", str);
  // Not returning anything. `str` is modified directly.
}

//-----------------------------------------------------------------------------

// Do not change the lines above and below the main function. These
// are here to ensure that the main() function defined here does not
// Conflict with the automarker when testing your code. Changing them
// will result in a 0 for this exercise. You are free to change anything
// inside the main() function itself.
#ifndef __testing__
int main()
{
  printf("%d\n", is_substring("Yo wag1 you pussy", "wag1"));

  char str1[MAX_STRING_LEN] = "Yo wag1 you pussy";

  replaceSubstring(str1, "wag1 you pussy", "Yo");

  char str[MAX_STRING_LEN] = "CSCA48 Exercise 3";

  replaceSubstring(str, "A48 Ex", "A48 sUMMER");

  // This should replace the substring:
  replaceSubstring(str, "A48 Ex", "A48 sUMMER Ex");

  // This should NOT replace anything, since some of the letters
  // in `a` have a different capitalization than in the string, so it is
  // NOT a valid substring.
  replaceSubstring(str, "summer", "Winter");

  // This should change the capitalization of the substring:
  changeSubstringCase(str, "sUMMER");

  char str2[MAX_STRING_LEN] = "csca48 g";
  // This should NOT change the capitalization, since the corresponding letters
  // in `a` are lowercase, and it is not a valid substring.
  changeSubstringCase(str2, "csca48");

  printf("Expected result: \"CSCA48 Summer Exercise 3\"\n");
  printf("Your solution: \"%s\"\n", str);
  return 0;
}
#endif
