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

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

#include "charset.h"
#include "imagebuffer.h"
#include "testimage.h"

struct charset *
charset_read_from_directory(const char directory[])
{
	DIR *dir = opendir(directory);

	size_t cwd_size = 100;
	char *cwd = malloc(cwd_size);

	errno = 0;
	while (getcwd(cwd, cwd_size) == NULL)
		{
			if (errno != ERANGE)
				{
					exit(EXIT_FAILURE);
				}

			cwd_size *= 1.5;

			if ((cwd = realloc(cwd, cwd_size)) == NULL)
				{
					exit(EXIT_FAILURE);
				}

			errno = 0;
		}

	if (chdir(directory) != 0)
		{
			exit(EXIT_FAILURE);
		};

	struct charset *png_charset =
		malloc(sizeof(*png_charset) + 100 * sizeof(*png_charset->characters));
	*png_charset = (struct charset) {
		.width = 0,
		.height = 0,
		.n = 100
	};

	size_t i = 0;
	for (struct dirent * dirent = readdir(dir); dirent != NULL;
			 dirent = readdir(dir))
		{
			struct imagebuffer *font_image =
				new_imagebuffer_from_png(dirent->d_name);
			if (font_image == NULL)
				{
					continue;
				}

			if (png_charset->width == 0 || png_charset->height == 0)
				{
					png_charset->width = font_image->width;
					png_charset->height = font_image->height;
				}

			assert(png_charset->width == font_image->width);
			assert(png_charset->height == font_image->height);

			char character = ' ';
			if (dirent->d_name[1] == '.')
				{
					character = dirent->d_name[0];
				}
			else
				{
					switch (dirent->d_name[0])
						{
						case 'd':
							character = '$';
							break;
						case 's':
							character = '/';
							break;
						case 'p':
							character = '|';
							break;
						}
				}

			unsigned char *glyph = malloc(png_charset->width *
			                              png_charset->height *
			                              color_type_to_bytes(PNG_COLOR_TYPE_GRAY));
			memset(glyph, 0, png_charset->width * png_charset->height);

			compose(&(struct imagebuffer) {
					.color_type = PNG_COLOR_TYPE_GRAY,
						.pixel_size = color_type_to_bytes(PNG_COLOR_TYPE_GRAY),
						.width = png_charset->width,
						.height = png_charset->height,
						.buffer = glyph
						},
				font_image,
				0, 0);

			png_charset->characters[i] = (struct chardesc)
			{
				.character = character,
				.glyph = glyph
			};

			++i;

			free(font_image);
		}

	png_charset->n = i;
	png_charset = realloc(png_charset,
												sizeof(*png_charset) +
												png_charset->n * sizeof(*png_charset->characters));

	assert(i != 0);

	if (chdir(cwd) != 0)
		{
			exit(EXIT_FAILURE);
		};

	free(cwd);
	closedir(dir);

	return png_charset;
}

void
free_charset(struct charset *charset)
{
	for (size_t i = 0; i < charset->n; ++i)
		{
			free(charset->characters[i].glyph);
		}
	
	free(charset);
}
