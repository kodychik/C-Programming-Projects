/**
 * Exercise 2 - FUNctions!
 *
 * Please read the comments below carefully, they describe your task in detail.
 * Any clarifications and corrections will be posted to Piazza so please keep
 * an eye on the forum!
 *
 * Starter code: Mustafa Quraish & Charles Xu, 2022
 */

#include <stdio.h>
// No additional imports allowed.
// You can make helper functions if you wish.

//-----------------------------------------------------------------------------

int is_prime(int check_val)
{
  /**
   * If `check_val` is a positive prime number (e.g., 2, 3, 5, 7, 11, etc)
   * return 1, otherwise return 0
   */
  int i;

  if (check_val <= 1){
    return 0;
  }

  else if (check_val % 2 == 0 && check_val != 2){
    return 0;
  }

  else if (check_val == 2){
    return 1;
  }

  for (i = 2; i < check_val / 2; i++){
    if (check_val % i == 0) return 0;
  }
  return 1;

}

float calculate_gpv(int grade)
{
  /**
   * Given grade as a percentage course grade, return the corresponding grade
   * point value as calculated by the University of Toronto grading scheme
   * (https://www.utsc.utoronto.ca/registrar/u-t-grading-scheme)
   * If grade is not a valid grade, return -1.
   */
  if (0 > grade || grade > 100) return -1;

  if (90 <= grade && grade <= 100){
    return 4.0;
  }
  else if (85 <= grade && grade < 90){
    return 4.0;
  }
  else if (80 <= grade && grade < 85){
    return 3.7;
  }
  else if(77 <= grade && grade < 79){
    return 3.3;
  }
  else if (73 <= grade && grade < 77){
    return 3.0;
  }
  else if (70 <= grade && grade < 73){
    return 2.7;
  }
  else if (67 <= grade && grade < 70){
    return 2.4;
  }
  else if (63 <= grade && grade < 67){
    return 2.0;
  }
  else if (60 <= grade && grade < 63){
    return 1.7;
  }
  else if (57 <= grade && grade < 60){
    return 1.3;
  }
  else if (53 <= grade && grade < 57){
    return 1.0;
  }
  else if (50 <= grade && grade < 53){
    return 0.7;
  }
  return 0.0;
}

//-----------------------------------------------------------------------------

// Do not change the macro definition above and below the main function.
// These are here to ensure that the main() function defined here does not
// Conflict with the automarker when testing your code. Changing them
// will result in a 0 for this exercise. You are free to change anything
// inside the main() function itself.
#ifndef __testing__
int main()
{
  int prime_result1 = is_prime(7);
  int prime_result2 = is_prime(4);
  if (prime_result1 == 1 && prime_result2 == 0)
  {
    printf("- is_prime() returning correct results for sample input\n");
  }
  else
  {
    printf("- is_prime() not returning correct results for sample input\n");
  }


  float gpv_result1 = calculate_gpv(93);
  float gpv_result2 = calculate_gpv(75);
  printf("- calculate_gpv():\n");
  printf("\tExpected result: 93 -> 4.0, 75 -> 3.0\n");
  printf("\tYour solution: 93 -> %.1f, 75 -> %.1f\n", gpv_result1, gpv_result2);

  printf("%d\n", is_prime(2));
  printf("%d\n", is_prime(1));
  printf("%d\n", is_prime(3));
  printf("%d\n", is_prime(5683));
  printf("%d\n", is_prime(5681));
  printf("%d\n", is_prime(5687));

  printf("%f\n", calculate_gpv(-1));
  printf("%f\n", calculate_gpv(100));
  printf("%f\n", calculate_gpv(53));
  printf("%f\n", calculate_gpv(75));
  printf("%f\n", calculate_gpv(22));
  printf("%f\n", calculate_gpv(18));
  printf("%f\n", calculate_gpv(95));
  printf("%f\n", calculate_gpv(64));
  printf("%f\n", calculate_gpv(67));
  return 0;
}
#endif
