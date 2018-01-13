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
n * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SLIDES_H
#define SLIDES_H

#include "asciibufferfill.h"
#include "asciibufferssim.h"
#include "asciibuffer.h"
#include "imagebuffer.h"

struct slide
{
	struct imagebuffer *image_background,
	  *image_foreground;
	struct asciibuffer *cache_composed,
		*cache_background,
		*cache_foreground,
		*cache_dialog;

	char *message;
	size_t dialogs_count;
	struct dialog **dialogs;
	struct dialog *in_dialogs[];
};

struct slide_context
{
	struct slide *current;
	int width, height;
};

struct slide_context *
slides_init(struct slide *slides);

void slides_loop(struct slide_context *context);
void slides_next(struct slide_context *context);
void slides_prev(struct slide_context *context);
void slides_end(struct slide_context *context);

struct slide *
make_slide(struct imagebuffer *image_background,
           struct imagebuffer *image_foreground,
           char *message,
           struct dialog *dialogs[],
           size_t dialogs_count);
void free_slide(struct slide *slide);

#endif
