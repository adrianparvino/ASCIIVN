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

#include "asciibuffer.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<png.h>

struct asciibuffer *
new_asciibuffer(size_t width, size_t height)
{
	struct asciibuffer *asciibuffer =
		malloc(sizeof(struct asciibuffer) + width * height);

	*asciibuffer = (struct asciibuffer)
		{
			.height = height,
			.width = width,
			.color_type = PNG_COLOR_TYPE_GRAY,
			.buffer = asciibuffer->in_buffer
		};
	memset(asciibuffer->in_buffer, 0, width * height);

	return asciibuffer;
}

void
flatten(struct asciibuffer *asciibuffer)
{
	for (size_t i = 0; i < asciibuffer->width; ++i)
		{
			for (size_t j = 0; j < asciibuffer->height; ++j)
				{
					if (index(asciibuffer, i, j) == '\0')
						{
							index(asciibuffer, i, j) = ' ';
						}
				}
		}
}

void
clear(struct asciibuffer *asciibuffer)
{
	memset(asciibuffer->buffer, 0, asciibuffer->height * asciibuffer->width);
}

void
show_asciibuffer(struct asciibuffer *asciibuffer)
{
	for (size_t i = 0; i < asciibuffer->height; ++i)
		{
			printf("%.*s\n", (int) asciibuffer->width,
			       asciibuffer->buffer + i * asciibuffer->width);
		}
}
