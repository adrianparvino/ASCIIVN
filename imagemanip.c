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
#include <math.h>
#include <stdio.h>
#include "imagemanip.h"

#define min(x, n) ((x) < (n) ? (x) : (n))
#define max(x, n) ((x) > (n) ? (x) : (n))

struct imagebuffer *side_by_side(struct imagebuffer *x,
                                 struct imagebuffer *y)
{
	assert(x->height == y->height);

	int width = (x->width + y->width);

	struct imagebuffer *imagebuffer = new_imagebuffer(width, x->height);
  
	for (int i = 0; i < x->height; ++i)
		{
			for (int j = 0; j < x->width; ++j)
				{
					imagebuffer->buffer[i*width + j] = x->buffer[i*x->width + j];
				}
		}
  
	for (int i = 0; i < y->height; ++i)
		{
			for (int j = 0; j < y->width; ++j)
				{
					imagebuffer->buffer[i*width + j + x->width] = y->buffer[i*y->width + j];
				}
		}

	return imagebuffer;
}

struct imagebuffer *top_bottom(struct imagebuffer *x,
                               struct imagebuffer *y)
{
	assert(x->width == y->width);

	int height = (x->height + y->height);

	struct imagebuffer *imagebuffer = new_imagebuffer(x->width, height);

	int i;
	for (i = 0; i < x->width * x->height; ++i)
		{
			imagebuffer->buffer[i] = x->buffer[i];
		}
  
	for (int j = 0; i < x->width * height; ++i, ++j)
		{
			imagebuffer->buffer[i] = y->buffer[j];
		}
  
	return imagebuffer;
}

void scale_nearest(struct imagebuffer *dest,
                   struct imagebuffer *src)
{
	for (int i = 0; i < dest->width; ++i) {
		for (int j = 0; j < dest->height; ++j) {
			size_t x = i * (src->width) / (dest->width);
			size_t y = j * (src->height) / (dest->height);
			
			index(dest, i, j) = index(src, x, y);
		}
	}
}

/* NB: Probably Broken Implementation */
void scale_bilinear(struct imagebuffer *dest,
                    struct imagebuffer *src)
{
	for (size_t j = 0; j < dest->height; ++j) {
		for (size_t i = 0; i < dest->width; ++i) {
			float x = ((float) i) / (dest->width - 1) * (src->width - 1);
			float y = ((float) j) / (dest->height - 1) * (src->height - 1);
			
			float xi, yi;
			float xf = modff(x, &xi),
				yf = modff(y, &yi);
			
			const int xi_ = min(xi + 1, src->width - 1);
			const int yi_ = min(yi + 1, src->height - 1);
			
			index(dest, i, j) =
				index(src, xi , yi )*(1 - xf)*(1 - yf) +
				index(src, xi_, yi )*(1 - yf)*xf +
				index(src, xi , yi_)*yf*(1 - xf) +
				index(src, xi_, yi_)*xf*yf;
		}
	}
}

struct imagebuffer *extract(size_t column_offset,
                            size_t row_offset,
                            size_t width,
                            size_t height,
                            struct imagebuffer *x)
{
	struct imagebuffer *extract_buffer = new_imagebuffer(width, height);

	for (size_t i = 0; i < height*width; ++i)
		{
			extract_buffer->buffer[i] =
				index(x, column_offset + i%width, row_offset + i/width);
		}

	return extract_buffer;
}
