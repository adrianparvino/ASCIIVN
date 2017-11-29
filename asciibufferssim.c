#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "asciibufferssim.h"
#include "asciibufferfill.h"

#include "charset.h"

#include <math.h>

#define pow2(x) (x*x)

int render_ssim(struct asciibuffer *dest,
                     unsigned char *source,
                     size_t width, size_t height,
                     char fontname[])
{
  struct charset *font_charset;
  size_t chardescs;
  if (!strcmp(fontname, ""))
    {
      fprintf(stderr, "Warning: no fontname provided. Using fallback.\n");
      font_charset = generate_test_charset(&chardescs);
    }

  for (int i = 0; i < width; i += font_charset->width)
    {
      for (int j = 0; j < height; j += font_charset->height)
	{
	  struct chardesc *best_ssim_char;
	  float best_ssim_value = 0;
	  for (int i = 0; i < chardescs; ++i)
	    {
	      int current_ssim_value =
		ssim__unsigned_char(font_charset->width*font_charset->height,
				    i*font_charset->width, j*font_charset->height,
				    width, width,
				    source, font_charset->characters[i].glyph
				    );
	      if (current_ssim_value > best_ssim_value)
		{
		  best_ssim_char = font_charset->characters + i;
		  best_ssim_value = current_ssim_value;
		}
	    }
	  dest->buffer[0] = best_ssim_char->character;
	}
    }
  
  return 0;

}

float ssim__unsigned_char(unsigned char n,
			  size_t column_offset,
			  size_t row_offset,
			  size_t row_width,
			  size_t image_width,
			  unsigned char x[n],
			  unsigned char y[n])
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
      size_t x_index = i/row_width*image_width + i%row_width + row_offset;
      float dx = x[x_index] - mean_x;
      float dy = y[i] - mean_y;
      
      mean_x += dx/(i + 1);
      mean_y += dy/(i + 1);

      comoment_xx += dx * (x[x_index] - mean_x);
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
