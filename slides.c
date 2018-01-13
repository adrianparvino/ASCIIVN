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
#include "slides.h"


void
render_slides(struct slides *slides, int width, int height)
{
	render_ssim(slides->cache_foreground, slides->image_foreground, "");
	render_fill(slides->cache_background, slides->image_foreground, "");
	compose((struct imagebuffer *) asciibuffer_bg,
	        (struct imagebuffer *) asciibuffer, 0 ,0);
	flatten(asciibuffer_bg);
	show_asciibuffer(asciibuffer_bg);
}

struct slides_context *
slides_init(struct slides *slides)
{
	struct slides_context *context = malloc(sizeof *context);

	*context = (struct slides_context) {
		.current = slides,
		.width = 0,
		.height = 0
	};

	
	return context;
}

void
slides_loop(struct slides_context *context)
{
	
}

void
slides_end(struct slides_context *context)
{

}

struct slides *
make_slide(struct imagebuffer *image_background,
           struct imagebuffer *image_foreground,
           struct dialog *dialogs,
           size_t dialogs_count)
{
	struct slides *slides = malloc(sizeof *slides);
	*slides = (struct slides) {
		.prev = NULL,
		.image_background = image_background,
		.image_foreground = image_foreground,
		.cache_background = NULL,
		.cache_foreground = NULL,
		.next = NULL
	};

	return slides;
}
