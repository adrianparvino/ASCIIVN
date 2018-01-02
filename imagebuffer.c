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

#define LENGTH(x) (sizeof(x) / sizeof(*x))

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <png.h>

#include "imagebuffer.h"

int
color_type_to_bytes(int color_type)
{
	switch (color_type)
		{
		case PNG_COLOR_TYPE_GRAY:
			return 1;
		case PNG_COLOR_TYPE_GRAY_ALPHA:
			return 2;
		default:
			printf("Currently unsupported color type.");
			exit(EXIT_FAILURE);
		}

}

struct imagebuffer *
new_imagebuffer(size_t width, size_t height)
{
	size_t size = width * height * color_type_to_bytes(DEFAULT_COLOR_TYPE);
	struct imagebuffer *imagebuffer = malloc(sizeof(struct imagebuffer) + size);

	*imagebuffer = (struct imagebuffer)
		{
			.width = width,
			.height = height,
			.color_type = DEFAULT_COLOR_TYPE,
			.pixel_size = color_type_to_bytes(DEFAULT_COLOR_TYPE),
			.buffer = imagebuffer->in_buffer
		};

	memset(imagebuffer->in_buffer, 0, size);

	return imagebuffer;
}

struct imagebuffer *
new_imagebuffer_from_png(char image_name[])
{
	FILE *image_file = fopen(image_name, "rb");
	if (image_file == NULL)
		{
			return NULL;
		}

	png_byte header[8];

	if (fread(header,
						sizeof(*header), LENGTH(header), image_file) < LENGTH(header))
		{
			fclose(image_file);
			return NULL;
		}

	if (png_sig_cmp(header, 0, sizeof(header)))
		{
			fclose(image_file);
			return NULL;
		}

	png_structp png_ptr = png_create_read_struct
		(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr)
		{
			fclose(image_file);
			exit(EXIT_FAILURE);
		}

	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
		{
			png_destroy_read_struct(&png_ptr, NULL, NULL);

			fclose(image_file);
			exit(EXIT_FAILURE);
		}

	png_infop end_info = png_create_info_struct(png_ptr);
	if (!end_info)
		{
			png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
			fclose(image_file);
			exit(EXIT_FAILURE);
		}

	if (setjmp(png_jmpbuf(png_ptr)))
		{
			// Error callback
			png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);

			fclose(image_file);
			exit(EXIT_FAILURE);
		}

	png_init_io(png_ptr, image_file);
	png_set_sig_bytes(png_ptr, LENGTH(header));

	png_read_info(png_ptr, info_ptr);

	png_color_16 *image_background;

	if (!png_get_bKGD(png_ptr, info_ptr, &image_background))
		{
			image_background =
				&(png_color_16) {
				.index = 255,
				.red = 65535,
				.blue = 65535,
				.green = 65535,
				.gray = 0
			};
		}

	int color_type = png_get_color_type(png_ptr, info_ptr),
		bit_depth = png_get_bit_depth(png_ptr, info_ptr);

	/* Normalize the colorspace to grayscale */
	switch (color_type)
		{
		case PNG_COLOR_TYPE_PALETTE:
			png_set_palette_to_rgb(png_ptr);
		case PNG_COLOR_TYPE_RGB:
		case PNG_COLOR_TYPE_RGB_ALPHA:
			png_set_rgb_to_gray(png_ptr, 1, -1, -1);
			break;

		case PNG_COLOR_TYPE_GRAY:
		case PNG_COLOR_TYPE_GRAY_ALPHA:
			if (bit_depth < 8)
				{
					png_set_expand_gray_1_2_4_to_8(png_ptr);
				}
			break;
		}
	/* Expand tRNS to alpha */
	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
		{
			png_set_tRNS_to_alpha(png_ptr);
		}
	/* Compress 16-bit to 8-bit */
	if (bit_depth == 16)
		{
			png_set_strip_16(png_ptr);
		}

	/* Set 0x00 to white and 0xff to black */
	png_set_invert_mono(png_ptr);

	png_read_update_info(png_ptr, info_ptr);

	int width = png_get_image_width(png_ptr, info_ptr),
		height = png_get_image_height(png_ptr, info_ptr),
		rowbytes = png_get_rowbytes(png_ptr, info_ptr);
	color_type = png_get_color_type(png_ptr, info_ptr);
	bit_depth = png_get_bit_depth(png_ptr, info_ptr);

	assert(color_type == PNG_COLOR_TYPE_GRAY ||
				 color_type == PNG_COLOR_TYPE_GRAY_ALPHA);

	png_bytep row_pointers[height];

	const int buffer_size = height * rowbytes;

	struct imagebuffer *imagebuffer =
		malloc(sizeof(*imagebuffer) + height * rowbytes);

	*imagebuffer = (struct imagebuffer)
	{
		.width = width,
		.height = height,
		.buffer = imagebuffer->in_buffer,
		.color_type = color_type,
		.pixel_size = color_type_to_bytes(color_type)
	};
	for (size_t i = 0; i < height; ++i)
		{
			row_pointers[i] = imagebuffer->buffer + i * rowbytes;
		}

	png_read_image(png_ptr, row_pointers);

	png_read_end(png_ptr, end_info);
	png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
	fclose(image_file);

	return imagebuffer;
}

unsigned char *
index_offset(struct imagebuffer *image, int x, int y, int offset)
{
	return &image->buffer[image->pixel_size*(image->width*y + x) + offset];
}

unsigned char *
index(struct imagebuffer *image, int x, int y)
{
	return index_offset(image, x, y, 0);
}

unsigned char *
index_alpha(struct imagebuffer *image, int x, int y)
{
	return index_offset(image, x, y, 1);
}
