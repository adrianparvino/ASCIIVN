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

#ifndef IMAGE_BUFFER_H
#define IMAGE_BUFFER_H

#include <stddef.h>

#define IMAGEBUFFER_BODY \
	size_t width, height; \
 \
	int background; \
	int pixel_size; \
	int color_type; \
 \
	unsigned char *buffer; \
	unsigned char in_buffer[];

struct imagebuffer
{
	IMAGEBUFFER_BODY
};

struct imagebuffer *new_imagebuffer(size_t width, size_t height);
struct imagebuffer *new_imagebuffer_from_png(char image_name[]);

int color_type_to_bytes(int color_type);

unsigned char *index_offset(struct imagebuffer *image, int x, int y, int offset);
unsigned char *index(struct imagebuffer *image, int x, int y);
unsigned char *index_alpha(struct imagebuffer *image, int x, int y);

#define DEFAULT_COLOR_TYPE PNG_COLOR_TYPE_GRAY_ALPHA

#endif
