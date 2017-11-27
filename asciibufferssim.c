#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "asciibufferssim.h"
#include "asciibufferfill.h"

#include "fonts/FixedsysExcelsior/backslash.xbm"
#include "fonts/FixedsysExcelsior/slash.xbm"

#include <math.h>

#define rotr8(x) ((x >> 1) | ((x & 1) << 7))
#define pow2(x) (x*x)

unsigned char *xbm_to_char_arr(char *src, size_t width, size_t height);
float ssim__int(int n, int dest[n], int src[n]);

int render_ssim(struct asciibuffer *dest,
                     unsigned char *source,
                     size_t width, size_t height,
                     char fontname[])
{
  if (!strcmp(fontname, ""))
    {
      fprintf(stderr, "Warning: no fontname provided. Attempting fallback.");
    }

  return 0;
}

unsigned char *xbm_to_char_arr(char *src, size_t width, size_t height)
{
  unsigned char *dest = malloc(width*height);

  size_t i = 0;
  size_t row_index = 0;

  int bytes_per_row = (width + 7)/8; // Number of bytes per row, rounded up
  
  while(i < width*height)
    {
      for (size_t mask = 0x80, column_index = 0;
           column_index < width;
           ++column_index, ++i, mask = rotr8(mask))
        {
          printf("%lu\n", row_index*bytes_per_row + column_index/8);
          dest[i] = (src[row_index*bytes_per_row + column_index/8] & mask) ? 0xff : 0x00;
        }
      ++row_index;
    }

  return dest;
}

float ssim__int(int n, int x[n], int y[n])
{
  if (n == 0)
    {
      fprintf(stderr, "Error: The sizes of the compared images is 0");
      exit(1);
    }
  
  float mean_x = 0, mean_y = 0;
  float comoment_xx = 0, comoment_yy = 0, comoment_xy = 0;

  // Online computation for covariance, adapted for variance.
  // https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#Online
  for (int i = 0; i < n; ++i)
    {
      float dx = x[i] - mean_x;
      float dy = y[i] - mean_y;
      
      mean_x += dx/(i + 1);
      mean_y += dy/(i + 1);

      comoment_xx += dx * (x[i] - mean_x);
      comoment_yy += dy * (y[i] - mean_y);
      comoment_xy += dx * (y[i] - mean_y);
    }

  float var_x    = comoment_xx/n,
        var_y    = comoment_yy/n,
        covar_xy = comoment_xy/n;

  float L   = 255,
        k_1 = 0.01,
        k_2 = 0.03,
        c_1 = k_1*L,
        c_2 = k_2*L;

  // Direct translation of SSIM formula
  // https://en.wikipedia.org/wiki/Structural_similarity#Algorithm
  return ((2*pow2(mean_y) + pow2(c_1))*(2*covar_xy + c_2))/
    ((pow2(mean_x) + pow2(mean_y) + c_1)*(var_x+var_y+c_2));
}
