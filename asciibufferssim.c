#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "imagemanip.h"

#include "asciibufferssim.h"
#include "asciibufferfill.h"

#include "charset.h"
#include "fonts/FixedsysExcelsior/backslash.xbm"

#include <math.h>

#define pow2(x) ((x)*(x))

int render_ssim(struct asciibuffer *dest,
                struct imagebuffer *src,
                char fontname[])
{
  struct charset *font_charset = NULL;

  size_t chardescs;
  if (!strcmp(fontname, ""))
    {
      fprintf(stderr, "Warning: no fontname provided. Using fallback.\n");
      font_charset = generate_test_charset(&chardescs);
    }

  struct imagebuffer *src_scaled =
    new_imagebuffer(font_charset->width * dest->width,
                    font_charset->height * dest->height);
  scale_nearest(src_scaled, src);
  
  for (size_t y = 0, y_ = 0; y < src_scaled->height; y += font_charset->height, ++y_)
    {
      for (size_t x = 0, x_ = 0; x < src_scaled->width; x += font_charset->width, ++x_)
	{
	  char best_ssim_char = 0;
	  float best_ssim_value = 0.00001;

          struct imagebuffer glyph_imagebuffer =
            {
              .height = font_charset->height,
              .width = font_charset->width,
              .buffer = NULL
            };

	  for (size_t i = 0; i < chardescs; ++i)
	    {
              glyph_imagebuffer.buffer = font_charset->characters[i].glyph;
	      float current_ssim_value =
		ssim_imagebuffer(x,
                                 y,
                                 src_scaled,
                                 &glyph_imagebuffer
                                 );

	      if (current_ssim_value >= best_ssim_value)
		{
		  best_ssim_char = font_charset->characters[i].character;
		  best_ssim_value = current_ssim_value;
		}
	    }

	  dest->buffer[y_*(dest->width) + x_] = best_ssim_char;
	}
    }

  if (font_charset != NULL)
    free_charset(font_charset, chardescs);
  
  free(src_scaled);
  
  return 0;

}

float ssim_imagebuffer(size_t column_offset,
                       size_t row_offset,
                       struct imagebuffer *x,
                       struct imagebuffer *y)
{
  if (y->height * y->width == 0)
    {
      fprintf(stderr, "Error: The sizes of the compared images is 0");
      exit(1);
    }
  
  float mean_x = 0, mean_y = 0;
  float comoment_xx = 0, comoment_yy = 0, comoment_xy = 0;

  // Online computation for covariance, adapted for variance.
  // https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#Online
  for (int i = 0; i < y->height * y->width; ++i)
    {
      size_t x_index = i/(y->width)*(x->width) + i%(y->width)
                     + row_offset*(x->width) + column_offset;

      float dx = x->buffer[x_index] - mean_x;
      float dy = y->buffer[i] - mean_y;
      
      mean_x += dx/(i + 1);
      mean_y += dy/(i + 1);

      comoment_xx += dx * (x->buffer[x_index] - mean_x);
      comoment_yy += dy * (y->buffer[i] - mean_y);
      comoment_xy += dx * (y->buffer[i] - mean_y);
    }

  float var_x    = comoment_xx/(y->width),
        var_y    = comoment_yy/(y->width),
        covar_xy = comoment_xy/(y->width);

  float L   = 255,
        k_1 = 0.01,
        k_2 = 0.03,
        c_1 = k_1*L,
        c_2 = k_2*L;

  // Direct translation of SSIM formula
  // https://en.wikipedia.org/wiki/Structural_similarity#Algorithm
  return ((2*mean_x*mean_y + c_1)*(2*covar_xy + c_2))/
    ((pow2(mean_x) + pow2(mean_y) + c_1)*(var_x+var_y+c_2));
}
