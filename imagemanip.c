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
#include <stdlib.h>
#include "imagemanip.h"
#include "imagemanip_kernel.h"

#define min(x, n) ((x) < (n) ? (x) : (n))
#define max(x, n) ((x) > (n) ? (x) : (n))

struct imagebuffer *
side_by_side(struct imagebuffer *x, struct imagebuffer *y)
{
	assert(x->height == y->height);

	int width = (x->width + y->width);

	struct imagebuffer *imagebuffer = new_imagebuffer(width, x->height);

	compose(imagebuffer, x, 0, 0);
	compose(imagebuffer, y, x->width, 0);

	return imagebuffer;
}

struct imagebuffer *
top_bottom(struct imagebuffer *x, struct imagebuffer *y)
{
	assert(x->width == y->width);

	int height = (x->height + y->height);

	struct imagebuffer *imagebuffer = new_imagebuffer(x->width, height);

	compose(imagebuffer, x, 0, 0);
	compose(imagebuffer, y, 0, x->height);

	return imagebuffer;
}

void
scale_nearest(struct imagebuffer *dest, struct imagebuffer *src)
{
	for (int i = 0; i < dest->width; ++i)
		{
			for (int j = 0; j < dest->height; ++j)
				{
					size_t x = i * (src->width) / (dest->width);
					size_t y = j * (src->height) / (dest->height);

					*index_gray(dest, i, j) = *index_gray(src, x, y);
					if (dest->color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
						{
							unsigned char alpha = 0xff;
							if (src->color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
								{
									alpha = *index_alpha(src, x, y);
								}

							*index_alpha(dest, i, j) = alpha;
						}
				}
		}
}

/* NB: Probably Broken Implementation */
/* NB: Probably only works when `dest` > `src`. */
void
scale_bilinear(struct imagebuffer *dest, const struct imagebuffer *src)
{
	int n = dest->width*dest->height;
	
	const size_t denominatorx = dest->width;
	const size_t denominatory = dest->height;

	unsigned char *inbufferx0y0 = aligned_alloc(32, n * sizeof *inbufferx0y0);
	unsigned char *inbufferx0y1 = aligned_alloc(32, n * sizeof *inbufferx0y1);
	unsigned char *inbufferx1y0 = aligned_alloc(32, n * sizeof *inbufferx1y0);
	unsigned char *inbufferx1y1 = aligned_alloc(32, n * sizeof *inbufferx1y1);
	float         *inbufferxf   = aligned_alloc(32, n * sizeof *inbufferxf);
	float         *inbufferyf   = aligned_alloc(32, n * sizeof *inbufferyf);
	unsigned char *outbuffer    = aligned_alloc(32, n * sizeof *outbuffer);

	const float stepx = (float) (src->width  - 2) / (denominatorx - 1);
	const float stepy = (float) (src->height - 2) / (denominatory - 1);
 
	scale_bilinear_prepare
		(index_gray,
		 inbufferx0y0,
		 inbufferx0y1,
		 inbufferx1y0,
		 inbufferx1y1,
		 
		 inbufferxf,
		 inbufferyf,
		 
		 dest,
		 src,
		 
		 stepx,
		 stepy);

	scale_bilinear_kernel
		(inbufferx0y0,
		 inbufferx0y1,
		 inbufferx1y0,
		 inbufferx1y1,

		 inbufferxf,
		 inbufferyf,

		 n,

		 outbuffer);
	
	scale_bilinear_store
		(index_gray,
		 outbuffer,
		 dest);

	if (dest->color_type != PNG_COLOR_TYPE_GRAY_ALPHA) goto cleanup;
	if (src->color_type != PNG_COLOR_TYPE_GRAY_ALPHA) {
		for (size_t i = 0; i < n; ++i)
			{
				outbuffer[i] = 0xff;
			}
		goto cleanup;
	}

	scale_bilinear_prepare
		(index_alpha,
		 inbufferx0y0,
		 inbufferx0y1,
		 inbufferx1y0,
		 inbufferx1y1,
		 inbufferxf,
		 inbufferyf,

		 dest,
		 src,
		 
		 stepx,
		 stepy);

	scale_bilinear_kernel
		(inbufferx0y0,
		 inbufferx0y1,
		 inbufferx1y0,
		 inbufferx1y1,

		 inbufferxf,
		 inbufferyf,

		 n,

		 outbuffer);

	scale_bilinear_store
		(index_alpha,
		 outbuffer,
		 dest);
	
 cleanup:
	free(inbufferx0y0);
	free(inbufferx0y1);
	free(inbufferx1y0);
	free(inbufferx1y1);
	free(inbufferxf);
	free(inbufferyf);
	free(outbuffer);
}

struct imagebuffer *
extract(size_t column_offset,
        size_t row_offset,
        size_t width,
        size_t height,
        struct imagebuffer *x)
{
	struct imagebuffer *extract_buffer = new_imagebuffer(width, height);

	for (size_t i = 0; i < width; ++i)
		for (size_t j = 0; j < height; ++j)
			{
				*index_gray(extract_buffer, i, j) =
					*index_gray(x, column_offset + i, row_offset + j);
			}

	return extract_buffer;
}

// TODO: Compose with alpha awareness, done correctly.
void
compose(struct imagebuffer *bg,
				struct imagebuffer *fg,
        size_t column_offset,
        size_t row_offset)
{
	assert(fg->width + column_offset <= bg->width);
	assert(fg->height + row_offset <= bg->height);

	for (size_t i = 0; i < fg->width; ++i)
		{
			for (size_t j = 0; j < fg->height; ++j)
				{
					unsigned char fgalpha = 0xff;
					unsigned char bgalpha = 0xff; 
					
					if (fg->color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
						{
							fgalpha = *index_alpha(fg, i, j);
						}
					if (bg->color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
						{
							bgalpha = *index_alpha(bg, column_offset + i, row_offset + j);
							
							*index_alpha(bg, column_offset + i, row_offset + j) =
								fgalpha + bgalpha*(0xff - fgalpha)/0xff;
						}

					// TODO: Do not rely on float.
					float fg_ = ((float) *index_gray(fg, i, j) * fgalpha)/0xff;
					float bg_ = ((float) *index_gray(bg, column_offset + i, row_offset + j) * bgalpha)/0xff;
						
					*index_gray(bg, column_offset + i, row_offset + j) =
						fg_ + bg_*(0xff - fgalpha)/0xff;
				}
		}
}
