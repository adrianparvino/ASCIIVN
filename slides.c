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
#include "slides.h"
#include "dialog.h"

void
render_slides(struct slide *slide, int width, int height)
{
	if (slide->cache_composed != NULL) free(slide->cache_composed);
	if (slide->cache_background != NULL) free(slide->cache_background);
	if (slide->cache_foreground != NULL) free(slide->cache_foreground);
	if (slide->cache_dialog != NULL) free(slide->cache_dialog);
	
	slide->cache_composed = new_asciibuffer(width, height);
	slide->cache_background = new_asciibuffer(width, height);
	slide->cache_foreground = new_asciibuffer(width, height);
	slide->cache_dialog = new_asciibuffer(width, height);
	
	render_fill(slide->cache_background, slide->image_background, "");
	render_ssim(slide->cache_foreground, slide->image_foreground, "");
	render_dialogs(slide->cache_dialog,
	               slide->message,
	               slide->dialogs,
	               slide->dialogs_count,
	               0);
	
	compose((struct imagebuffer *) slide->cache_composed,
	        (struct imagebuffer *) slide->cache_background, 0, 0);
	compose((struct imagebuffer *) slide->cache_composed,
	        (struct imagebuffer *) slide->cache_foreground, 0, 0);
	compose((struct imagebuffer *) slide->cache_composed,
	        (struct imagebuffer *) slide->cache_dialog,
	        0, height - slide->cache_dialog->height);
	
	flatten(slide->cache_background);
}

struct slide_context *
slides_init(struct slide *slide)
{
	struct slide_context *context = malloc(sizeof *context);

	*context = (struct slide_context) {
		.current = slide,
		.width = 0,
		.height = 0
	};

	
	return context;
}

void
slides_loop(struct slide_context *context)
{
	
}

void
slides_end(struct slide_context *context)
{

}

struct slide *
make_slide(struct imagebuffer *image_background,
           struct imagebuffer *image_foreground,
           char *message,
           struct dialog *dialogs[],
           size_t dialogs_count)
{
	struct slide *slide = malloc(sizeof *slide +
	                               dialogs_count*sizeof(struct dialog *));
	char *message_ = malloc(strlen(message) + 1);
	
	*slide = (struct slide) {
		.image_background = image_background,
		.image_foreground = image_foreground,
		.cache_background = NULL,
		.cache_foreground = NULL,
		.message = message_,
		.dialogs_count = dialogs_count,
		.dialogs = slide->in_dialogs
	};

	strcpy(slide->message, message);
	for(size_t i = 0; i < dialogs_count; ++i)
		{
			slide->dialogs[i] = dialogs[i];
		}

	return slide;
}
