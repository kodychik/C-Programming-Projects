#include <stdio.h>

#ifndef __testing__
/**
 * Prints out the sudoku in an easy-to-view format. Feel free to change
 * this function if you need to help you debug.
 */
void print_sudoku(int sudoku[9][9])
{
  printf("The Sudoku contains:\n");
  printf("+-------+-------+-------+\n");
  for (int j = 0; j < 9; j++)
  {
    printf("| ");
    for (int i = 0; i < 9; i++)
    {
      printf("%d ", sudoku[j][i]);
      if (i % 3 == 2)
        printf("| ");
    }
    printf("\n");
    if (j % 3 == 2)
      printf("+-------+-------+-------+\n");
  }
}
#endif

int inArray(int x, int arr[9])
{
  for (int i = 0; i < 9; i++)
  {
    if (arr[i] == x) return -1;
  }
  return 1;
}

void initializeArray(int arr[9])
{
  for (int i = 0; i < 9; i++)
  {
    arr[i] = -1;
  }
}

/*****************************************************************************/

/**
 * This function checks if the current sudoku grid (not necessarily
 * complete) is valid. This means that (ignoring the 0s), each row, column
 * and 3x3 subgrid should not repeat any digits 1-9.
 *
 * Returns 1 if the sudoku is valid, or 0 if it's not.
 */
int is_valid_sudoku(int sudoku[9][9])
{
  // need to
  int i,j,k;
  int base = 0;
  int base2 = 0;
  int count = 0;
  int rowArray[9];
  int colArray[9];
  // sudoku[0][0], [0][3], [0][6], [3][0], [3][3], [3][6], [6][0], [6][3], [6][6]


  // for rows and columns
  for (i = 0; i < 9; i++)
  {
    initializeArray(rowArray);
    initializeArray(colArray);
    for (j = 0; j < 9; j++)
    {
      if (sudoku[i][j] < 0 || sudoku[i][j] > 9)
      {
        //printf("i: %d, j: %d\n", i, j);
        return 0;
      }
      if (sudoku[i][j] != 0 && inArray(sudoku[i][j], rowArray) == -1)
      {
        //printf("i: %d, j: %d\n", i, j);
        return 0;
      }
      
      rowArray[j] = sudoku[i][j];

      if (sudoku[j][i] < 0 || sudoku[j][i] > 9)
      {
        //printf("i: %d, j: %d\n", i, j);
        return 0;
      }
      
      if (sudoku[j][i] != 0 && inArray(sudoku[j][i], colArray) == -1)
      {
        //printf("i: %d, j: %d\n", j, i);
        return 0;
      }
      colArray[j] = sudoku[j][i];
    }
  }

  // for (3 x 3) mini sudokus
  
  for (i = 0; i < 9; i++)
  {
    initializeArray(rowArray);
    for (j = 0; j < 3; j++)
    {
      for (k = 0; k < 3; k++)
      {
        if (sudoku[base + j][base2 + k] != 0 && inArray(sudoku[base + j][base2 + k], rowArray) == -1)
        {
          //printf("row: %d, column: %d\n", base+j, base2+k);
          return 0;
        }
        if (sudoku[base + j][base2 + k] != 0) rowArray[count] = sudoku[base + j][base2 + k];
        count++;
      }
    }
    base2 += 3;
    if (base2 > 6)
    {
      base2 = 0;
      base += 3;
    }
    count = 0;
  }

  return 1; // Fix this to return the correct value!
}
/*
int *generateArray()
{
  int arr[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  return arr;
}

int getFirstElement(int array[9])
{
  for (int i = 0; i < 9; i++)
  {
    if (array[i] != 0) return array[i];
  }
}*/
/**
 * Given a (possibly partially) completed sudoku grid, try and solve the
 * sudoku. The `sudoku` array should be changed to contain the solution if
 * one exists. None of digits in the input grid should be changed.
 * 
 * NOTE: The empty spots are denoted with 0s in them.
 *
 * Refer to the handout for more discussion on how to implement this.
 *
 * Return 1 if the sudoku was solved, and update the `sudoku` parameter.
 * Return 0 if it's not possible to solve the sudoku, and leave the input
 *    `sudoku` array unchanged in this case.
 */


int solve_sudoku(int sudoku[9][9])
{
  // base case
  int i, j, k;
  for (i = 0; i < 9; i++)
  {
    for (j = 0; j < 9; j++)
    {
      if (sudoku[i][j] == 0)
      {
        for (k = 1; k < 10; k++)
        {
          if (is_valid_sudoku(sudoku) == 1)
          {
            sudoku[i][j] = k;

            if (solve_sudoku(sudoku) == 1) return 1;
            else sudoku[i][j] = 0;
          }
        }
        return 0;
        //solve_sudoku(sudoku)
      }
      //if (is_valid_sudoku(sudoku) == 0 && sudoku[i][j] == 9) break;
    }
  }
  
  if (is_valid_sudoku(sudoku) == 0) return 0;

  return 1; // Fix this to return the correct value!
}

#ifndef __testing__

int main()
{
  /**
   * This example is the one from the Wiki, but your solution should be able
   * to handle any solvable sudoku. The time to solve different puzzles may
   * vary, but ideally it should not take more than a second for this one.
   */
  /*
  int sudoku_grid[9][9] = {
      {5, 3, 0, 0, 7, 0, 0, 0, 0},
      {6, 0, 0, 1, 9, 5, 0, 0, 0},
      {0, 9, 8, 0, 0, 0, 0, 6, 0},
      {8, 0, 0, 0, 6, 0, 0, 0, 3},
      {4, 0, 0, 8, 0, 3, 0, 0, 1},
      {7, 0, 0, 0, 2, 0, 0, 0, 6},
      {0, 6, 0, 0, 0, 0, 2, 8, 0},
      {0, 0, 0, 4, 1, 9, 0, 0, 5},
      {0, 0, 0, 0, 8, 0, 0, 7, 9}};*/

  int sudoku_grid[9][9] = {

      {8, 0, 0, 0, 0, 0, 0, 0, 0},

      {0, 0, 3, 6, 0, 0, 0, 0, 0},

      {0, 7, 0, 0, 9, 0, 2, 0, 0},

      {0, 5, 0, 0, 0, 7, 0, 0, 0},

      {0, 0, 0, 0, 4, 5, 7, 0, 0},

      {0, 0, 0, 1, 0, 0, 0, 3, 0},

      {0, 0, 1, 0, 0, 0, 0, 6, 8},

      {0, 0, 8, 5, 0, 0, 0, 1, 0},

      {0, 9, 0, 0, 0, 0, 4, 0, 0}};

  if (is_valid_sudoku(sudoku_grid) == 1) printf("Sudoku is Valid!\n");
  else printf("Invalid Sudoku\n");
  
  print_sudoku(sudoku_grid);

  int solved = solve_sudoku(sudoku_grid);

  printf("\nsolve_sudoku() return value: %d\n\n", solved);

  /* Look at the handout to see the solution for this! */
  print_sudoku(sudoku_grid);

  return 0;
}

#endif