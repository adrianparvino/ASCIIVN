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

#ifndef ASCII_CHARSET_H
#define ASCII_CHARSET_H

#include<stddef.h>

struct chardesc
{
  char character;
  
  unsigned char *glyph;
};

struct charset
{
  size_t width, height;

  size_t n;
  struct chardesc characters[];
};

struct charset* read_from_directory(const char directory[]);
struct charset* generate_test_charset();
struct charset* generate_test_charset_ssim();
void free_charset(struct charset* charset);

#endif
