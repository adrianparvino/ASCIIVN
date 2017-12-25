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

#ifndef SLIDES_H
#define SLIDES_H

#include "asciibuffer.h"
#include "imagebuffer.h"

struct slides {
	struct slides *prev;
	struct imagebuffer image_background, image_foreground;
	struct asciibuffer cache_background, cache_foreground;
	struct slides *next;
};

void slides_init();
void next_slide(struct slides *slides);
void previous_slide(struct slides *slides);
void slides_end();
	
#endif

