#include <stdio.h>

// Define the image size we are using
#define SIZEX 50
#define SIZEY 50

// Include the functions to read / write the images
#include "imgUtils.c"

void find_connected_region(unsigned char input[SIZEY][SIZEX], int px, int py,
                           unsigned char output[SIZEY][SIZEX])
{
  /**
   * The function takes in the input image array (input) representing the
   * elevation maps of our newly discovered planet, and the initial position
   * of the rover (px, py). Each element of `input` has values 0-255 inclusive.
   * Each element of the array represents the color of the corresponding pixel,
   * where 0 represents the colour black, and 255 represents the colour white.
   *
   * NOTE: Because of how 2D arrays are stored in memory, we need to be careful
   *       when trying to access the correct pixel. PGM images use the math
   *       convention where the first index is the ROW, and the second index
   *       is the COLUMN. So, to get the color of pixel (x, y), you will
   *       need to do:
   *                                input[y][x]
   *
   *
   * Given
   * - The input elevation map in `input`
   * - An initially empty image called `output` (all the pixels have colour 0)
   * - And initial coordinates of the rover (px, py)
   *
   * Your task is to find all *connected* pixels that have the same elevation
   * as the one at (px,py) in `input`, and mark these pixels on `output`.
   *
   * For instance, if the initial coordinates are (px=5, py=10), your program
   * must check the elevation at input[10][5], then set the colour of all
   * connected pixels to white (255) in the levelset_map.
   *
   * Example with a very tiny sample image:
   *
   * input:
   *                       1    1    1    2    3    3
   *                       1    1    2    3    3    4
   *                       1    2    2    2    4    3
   *                       1    1    1    2    4    3
   *                       1    1    2    2    3    3
   *                       4    4    4    4    2    2
   *
   *
   * If we call the function with the `input` above, and initial coordinates
   * (1,1), it should produce
   *
   * output:
   *
   *                      255  255  255   0    0    0
   *                      255  255   0    0    0    0
   *                      255   0    0    0    0    0
   *                      255  255  255   0    0    0
   *                      255  255   0    0    0    0
   *                       0    0    0    0    0    0
   *
   * If we call the function with initial coordinates (4, 0) it will produce
   *
   * output:
   *
   *                       0    0    0    0   255  255
   *                       0    0    0   255  255   0
   *                       0    0    0    0    0    0
   *                       0    0    0    0    0    0
   *                       0    0    0    0    0    0
   *                       0    0    0    0    0    0
   *
   * In effect, this function extracts the connected region in the image
   * array with the same elevation as that of the pixel at (px, py).
   *
   * NOTE: A pixel can be 'connected' to it's it's 4 neighbours above, below,
   *       to the left and right of it, if they have the same colour. In
   *       particular, we will NOT count pixels along the diagonal. Carefully
   *       look at the examples above to make sure you understand this.
   *
   * - You should NOT change the contents of the input array.
   *
   * There are many ways to approach this problem, you're free to choose
   * whatever makes more sense to you. Make reasonable assumptions where
   * needed, and solve the problem!
   */
  if (px < 0 || py < 0 || px > SIZEX - 1 || py > SIZEY - 1 || output[py][px] == 255 || output[py][px] != 0) return; // 

  //printf("px: %d, py: %d\n", px, py);

  output[py][px] = 255;

  if (input[py][px] == input[py - 1][px]) // top && output[py - 1][px] == 0
  {
    find_connected_region(input, px, py - 1, output);
  }

  if (input[py][px] == input[py][px + 1]) // right && output[py][px + 1] == 0
  {
    find_connected_region(input, px + 1, py, output);
  }

  if (input[py][px] == input[py + 1][px]) // bottom && output[py + 1][px] == 0
  {
    find_connected_region(input, px, py + 1, output);
  }

  if (input[py][px] == input[py][px - 1]) // left && output[py][px - 1] == 0
  {

    find_connected_region(input, px - 1, py, output);
  }

  return; // Update the `output` array as needed before returning.
}

// ----------------------------------------------------------------------------

#ifndef __testing__ // You know the drill, don't remove this.

int main()
{
  unsigned char input[SIZEY][SIZEX];
  unsigned char output[SIZEY][SIZEX];

  // Initialize output array to have colour black (0)
  for (int y = 0; y < SIZEY; y++)
  {
    for (int x = 0; x < SIZEX; x++)
    {
      output[y][x] = 0;
    }
  }

  // --------------------------------------------------------------------------
  //                      Testing with floo-region-1.pgm
  //                     Output file will be output-1.pgm
  // --------------------------------------------------------------------------

  // Read the selected input image into input[][]
  readPGM("floo-region-1.pgm", &input[0][0]);

  printf("Calling find_connected_region() on image 1...\n");
  find_connected_region(input, 49, 0, output); // Staring position is (24, 16)

  // Write the connected region to the output image
  writePGM("output-1.pgm", &output[0][0]);

  // --------------------------------------------------------------------------
  //                      Testing with floo-region-2.pgm
  //                     Output file will be output-2.pgm
  // --------------------------------------------------------------------------

  // Read the selected input image into input[][]
  readPGM("floo-region-2.pgm", &input[0][0]);

  // Don't forget to reset the output array!
  for (int y = 0; y < SIZEY; y++)
  {
    for (int x = 0; x < SIZEX; x++)
    {
      output[y][x] = 0;
    }
  }

  printf("Calling find_connected_region() on image 2...\n");
  find_connected_region(input, 49, 49, output); // Starting position is (4, 35)

  // Write the connected region to the output image
  writePGM("output-2.pgm", &output[0][0]);

  printf("Done!\n");
  return 0;
}

#endif
