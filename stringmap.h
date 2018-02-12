/* This file is part of ASCIIVN.
 *
 * Copyright (C) 2018  Adrian Parvin D. Ouano
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

#ifndef STRING_MAP_H
#define STRING_MAP_H

#include "imagebuffer.h"
#include "slides.h"
#include <stddef.h>

struct string_map
{
	struct string_map *left;
	struct string_map *right;

	char *key;
	
	struct slide **slides[];
};

void
string_map_append(struct string_map **map,
                  char key[],
                  struct slide **value);
struct slide ***
string_map_index(struct string_map *map,
                 char key[]);

#endif
