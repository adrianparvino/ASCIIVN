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

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

#include "asciibufferfill.h"
#include "imagemanip.h"
#include "charset.h"

#define LENGTH(x) (sizeof(x) / sizeof(*x))

struct cache
{
	float value;
	char character;
};

int
cmp_cache(const void *x, const void *y)
{
	return ceil(((const struct cache *) x)->value -
							((const struct cache *) y)->value);
}

void
render_fill(struct asciibuffer *dest,
						const struct imagebuffer *src,
            const char fontname[])
{
	clear(dest);
	struct charset *font_charset = NULL;

	if (!strcmp(fontname, ""))
		{
			fprintf(stderr, "Warning: no fontname provided. Using fallback.\n");

			font_charset = charset_read_from_directory("./fonts/FixedsysExcelsior");
		}

	scale_bilinear((struct imagebuffer *) dest, src);

	struct cache cache[font_charset->n];

	for (size_t character = 0; character < font_charset->n; ++character)
		{
			// Calculate the arithmetic mean of the glyph
			cache[character].value = 0;
			
			for (size_t i = 0; i < font_charset->width * font_charset->height; ++i)
				{
					float dx = font_charset->characters[character].glyph[i] -
						cache[character].value;
					cache[character].value += dx / (i + 1);
				}

			cache[character].character =
				font_charset->characters[character].character;
		}

	qsort(cache, font_charset->n, sizeof(*cache), cmp_cache);

	for (size_t i = 0; i < dest->width; ++i)
		{
			for (size_t j = 0; j < dest->height; ++j)
				{
					char best_character = 0;

					for (size_t k = 0; k < LENGTH(cache); ++k)
						{
							if (*index((struct imagebuffer *) dest, i, j) < cache[k].value)
								{
									break;
								}

							best_character = cache[k].character;
						}

					*index((struct imagebuffer *) dest, i, j) = best_character;
				}
		}

	free_charset(font_charset);
}
