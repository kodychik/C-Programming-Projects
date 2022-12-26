
#include <stdio.h>
#include <stdlib.h>
// NO additional imports allowed. You *can* make helper functions if you wish.

#define MAX_STRING_LEN 1024

int str_len(char *string)
{
  int i = 0;
  char *ptr = NULL;
  ptr = string;

  while (*(ptr + i) != '\0'){
    i = i + 1;
  }
  return i;

}

int find_reverse_index(char *string, char *a)
{
  int i, j, first_occ;
  i = str_len(string), j = 0;
  char *ptr = NULL;
  char *qtr = NULL;
  ptr = string;
  qtr = a;


  while (i >= 0)
  {
    while (*(ptr + i) != *(qtr) && i >= 0)
    {
      i--;
    }
    if (i == 0 && *(ptr + i) != *(qtr + i)) return -1;
    first_occ = i;

    while (*(ptr + i) == *(qtr + j) && *(ptr + i) != '\0' && *(qtr + j) != '\0')
    {
      i++;
      j++;
    }

    if (*(qtr + j) == '\0') return first_occ;


    i = first_occ - 1;
    j = 0;


  }
  return -1;

}
 

void *shift_left(char *string, int start_index)
{
  int i;
  for (i = start_index; i < str_len(string); i++)
  {
    *(string + i) = *(string + i + 1);
  }
  *(string + i) = '\0';
}

char *find_last_substring(char *str, char *a)
{
  /**
   * Given a string `str` and another string `a`, return a pointer to the start
   * of the *LAST* occurrence of `a` in `str`. (Unlike ex3, where you had to
   * find the FIRST occurrence).
   *
   * For instance, if we had:                       (here)
   *                                                  V
   *      char str[MAX_STRING_LEN] = "Hello everyone, Hello world!"
   *      char *res = find_last_substring(str, "Hello");
   *
   * then, we would except `res` to be a pointer to the character marked above.
   * In particular, since the second "Hello" is at index 16, we should get
   * the following:
   *
   *      res - str == 16;      (This is pointer arithmetic)
   *
   * If `a` is not a valid substring of `str`. return NULL.
   */
  int index;

  char *ptr = NULL;
  ptr = str;

  char *qtr = NULL;
  qtr = a;

  if (find_reverse_index(ptr, qtr) == -1) return NULL;

  index = find_reverse_index(ptr, qtr);

  return (ptr + index); // Replace with correct return
}

void split_vowels(char *str, char *vowels)
{

  /**
   * Move all of the vowels from `str` (in the order of appearance) to the
   * string `vowels`. (ie, after the function call `str` should not have any
   * vowels in it). You may assume there is enough space allocated in `vowels`.
   *
   * Look at the test case below for an example.
   */

   // Not returning anything. `str` and `vowels` modified directly.
  char *ptr = NULL;
  char *qtr = NULL;
  ptr = str;
  qtr = vowels;
  int i, j;
  j = 0;

  for (i = 0; *(ptr + i) != '\0'; i++)
  {
    if (*(ptr + i) == 'a' || *(ptr + i) == 'e' || *(ptr + i) == 'i' || *(ptr + i) == 'o' || *(ptr + i) == 'u' || *(ptr + i) == 'A' 
    || *(ptr + i) == 'E' || *(ptr + i) == 'I' || *(ptr + i) == 'O' || *(ptr + i) == 'U')
    {
      *(qtr + j) = *(ptr + i);
      j++;
      shift_left(ptr, i);
      i--;
    }
    
  }
  *(qtr + j) = '\0';


}

// ----------------------------------------------------------------------------

// Do not change the lines above and below the main function. These
// are here to ensure that the main() function defined here does not
// Conflict with the automarker when testing your code. Changing them
// will result in a 0 for this exercise. You are free to change anything
// inside the main() function itself.
#ifndef __testing__
int main()
{

  char my_str1[MAX_STRING_LEN] = "aeiouaeiouaeiouAEIOU A";
  char vowels[MAX_STRING_LEN];
  for(int i = 0; i < MAX_STRING_LEN; i++) {
    vowels[i] = 'a';
  }

  char *res1 = find_last_substring(my_str1, " ");
  if (res1 - my_str1 == 20) printf("Returned correct result for find_last_substring fcn\n");


  split_vowels(my_str1, vowels);
  printf("%s\n", my_str1);
  printf("%s\n", vowels);





  // untouched started code
  char my_str[MAX_STRING_LEN] = "many many people have many many hobbies";
  char *res = find_last_substring(my_str, "many");
  if (res - my_str == 27)
  {
    printf("- find_last_substring() returned the correct result!\n");
  }
  else
  {
    printf("! find_last_substring() did not work properly.\n");
  }

  printf("----------------------------------------------------------------\n");

  char str[MAX_STRING_LEN] = "This sentence has many vowels! AEIOU";
  //char vowels[MAX_STRING_LEN];
  split_vowels(str, vowels);

  printf("(Expected Result) str: \"Ths sntnc hs mny vwls! \", "
         "vowels: \"ieeeaaoeAEIOU\"\n");
  printf("(Your Solution) str: \"%s\", vowels: \"%s\"\n", str, vowels);
}
#endif
