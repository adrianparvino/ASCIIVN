/* This file is part of ASCIIVN.
 *
 * Copyright (C) 2017  Adrian Parvin D. Ouano
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "imagemanip.h"

#include "asciibufferssim.h"
#include "asciibufferfill.h"

#include <math.h>

#define index(image, x, y) ((image)->buffer[(int) (((int) (y)) * (image)->width + ((int) (x)))])
#define pow2(x) ((x)*(x))
#define signpow2(x) ((x)*fabsf(x))
#define pow3(x) ((x)*(x)*(x))

int render_ssim(struct asciibuffer *dest,
                struct imagebuffer *src,
                char fontname[])
{
	struct charset *font_charset = NULL;

	bool defaultfont = false;

	if (!strcmp(fontname, ""))
		{
			fprintf(stderr, "Warning: no fontname provided. Using fallback.\n");

			font_charset = generate_test_charset_ssim();
			defaultfont = true;
		}

	assert(src->width % font_charset->width == 0 && 
	       src->height % font_charset->height == 0);

	int result = render_ssim_charset_unsafe(dest, src, font_charset);

	if (defaultfont)
		{
			free_charset(font_charset);
		}
  
	return result;
}

int render_ssim_charset_unsafe(struct asciibuffer *dest,
                               struct imagebuffer *src,
                               struct charset *font_charset)
{
	for (size_t y_ = 0, y = 0; y < src->height; ++y_, y += font_charset->height)
		{
			for (size_t x_ = 0, x = 0; x < src->width; ++x_, x += font_charset->width)
				{
					char best_ssim_char = 0;
					float best_ssim_value = 0;

					struct imagebuffer glyph_imagebuffer =
						{
							.height = font_charset->height,
							.width = font_charset->width,
							.buffer = NULL
						};
              
					for (size_t i = 0; i < font_charset->n; ++i)
						{
							glyph_imagebuffer.buffer = font_charset->characters[i].glyph;

							float current_ssim_value =
								ssim_imagebuffer(x, y, src, &glyph_imagebuffer);

							if (current_ssim_value > best_ssim_value)
								{
									best_ssim_value = current_ssim_value;
									best_ssim_char = font_charset->characters[i].character;
								}

						}
					dest->buffer[y_*(dest->width) + x_] = best_ssim_char;
				}
		}

	return 0;
}

float ssim_imagebuffer(size_t column_offset,
                       size_t row_offset,
                       struct imagebuffer *x,
                       struct imagebuffer *y)
{
	if (y->height * y->width == 0)
		{
			fprintf(stderr, "Warning: The sizes of the compared images is 0");
			return 1;
		}

	float mean_x = 0, mean_y = 0;
	float comoment_xx = 0, comoment_yy = 0, comoment_xy = 0;

	size_t n = y->height * y->width;
  
	// Online computation for covariance, adapted for variance.
	// https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#Online
	for (size_t i = 0; i < n; ++i) {
		size_t x_index = (i/(y->width) + row_offset)*(x->width)
			+  i%(y->width) + column_offset;

		float dx = x->buffer[x_index] - mean_x;
		float dy = y->buffer[i] - mean_y;
      
		mean_x += dx/(i + 1);
		mean_y += dy/(i + 1);

		comoment_xx += dx * (x->buffer[x_index] - mean_x);
		comoment_yy += dy * (y->buffer[i] - mean_y);
		comoment_xy += dx * (y->buffer[i] - mean_y);
	}

	float var_x    = comoment_xx/n,
	      var_y    = comoment_yy/n,
	      covar_xy = comoment_xy/n;

	float L   = 255,
	      k_1 = 0.01,
	      k_2 = 0.03,
	      c_1 = pow2(k_1*L),
	      c_2 = pow2(k_2*L),
	      c_3 = c_2/2;

	// Direct translation of SSIM formula
	// https://en.wikipedia.org/wiki/Structural_similarity#Algorithm

	float luminance = (2*mean_x*mean_y + c_1)/(pow2(mean_x) + pow2(mean_y) + c_1),
		contrast = (2*sqrt(var_x)*sqrt(var_y) + c_2)/(var_x + var_y + c_2),
		structure = (covar_xy + c_3)/(sqrt(var_x)*sqrt(var_y) + c_3);

	return luminance*contrast*structure;
}
