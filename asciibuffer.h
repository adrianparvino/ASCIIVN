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

#ifndef ASCII_BUFFER_H
#define ASCII_BUFFER_H

#include<stddef.h>

struct asciibuffer
{
	size_t width, height;
	
	int background;
	int color_type;

	char *buffer;
	char in_buffer[];
};

struct asciibuffer *new_asciibuffer(size_t width, size_t height);
void flatten(struct asciibuffer *asciibuffer);
void clear(struct asciibuffer *asciibuffer);
void show_asciibuffer(struct asciibuffer *asciibuffer);

#endif
