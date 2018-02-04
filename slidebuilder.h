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

#ifndef SLIDE_BUILDER_H
#define SLIDE_BUILDER_H

#include "slides.h"
#include "stringmap.h"

struct slide *EOV_;
#define EOV (&EOV_)

struct slide_builder_context
{
	struct slide *current;
	
	struct string_map *map;
	struct slide ***fills;

	struct slide **current_fills[];
};

void slides_builder_scene(struct slide_builder_context *context,
                         char *name);
void slides_builder_slide(struct slide_builder_context *context,
                          struct imagebuffer *image_background,
                          struct imagebuffer *image_foreground,
                          char *message);
void slides_builder_slide_reply(struct slide_builder_context **context,
                                char *reply,
                                char *scene);
	
#endif
