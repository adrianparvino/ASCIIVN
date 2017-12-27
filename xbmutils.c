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

#include<malloc.h>

#include "xbmutils.h"

#define rotr8(x) ((x >> 1) | ((x & 1) << 7))
#define rotl8(x) (((x << 1) | ((x & 0x80) >> 7)) & 0xff)

unsigned char *
xbm_to_unsigned_char_arr(char *src, size_t width, size_t height)
{
	unsigned char *dest = malloc(width * height);

	size_t i = 0;
	size_t row_index = 0;

	int bytes_per_row = (width + 7) / 8;	// Number of bytes per row, rounded up

	while (i < width * height)
		{
			for (size_t mask = 0x01, column_index = 0;
					 column_index < width; ++column_index, ++i, mask = rotl8(mask))
				{
					dest[i] =
						(src[row_index * bytes_per_row + column_index / 8] & mask) ? 0xff
						: 0x00;
				}
			++row_index;
		}

	return dest;
}
