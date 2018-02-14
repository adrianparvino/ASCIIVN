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

#include <stdbool.h>
#include "slides.h"
#include "stringmap.h"

struct slide_builder_context {
	struct slide *root;
	struct slide *current;
	
	struct string_map_slide_next_ptr *map;
	char *fill_scene;

	char *current_fills[];
};

void 
slide_builder_scene(struct slide_builder_context **context,
                         char *name);
void 
slide_builder_slide(struct slide_builder_context **context,
                          struct imagebuffer *image_background,
                          struct imagebuffer *image_foreground,
                          char *message);
void 
slide_builder_slide_reply(struct slide_builder_context **context,
                          char *reply,
                          char *scene);

struct slide_builder_context *
slide_builder_init(struct imagebuffer *image_background,
                   struct imagebuffer *image_foreground,
                   char *message);

struct slide *
slide_builder_end(struct slide_builder_context *context);
#endif
