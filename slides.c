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
#include <stdbool.h>
#include "slides.h"
#include "terminal.h"
#include "dialog.h"

void
render_slides(struct slide *slide, int choice, int width, int height)
{
	bool dirty;
	if (!(slide->cache_composed != NULL &&
	      slide->cache_composed->width == width &&
	      slide->cache_composed->height == height))
		{
			free(slide->cache_composed);
			slide->cache_composed = new_asciibuffer(width, height);
			dirty = true;
		}
	
	if (!(slide->cache_background != NULL &&
	      slide->cache_background->width == width &&
	      slide->cache_background->height == height))
		{
			free(slide->cache_background);
			slide->cache_background = new_asciibuffer(width, height);
			dirty = true;
			render_fill(slide->cache_background, slide->image_background, "");
		}
	    
	if (!(slide->cache_foreground != NULL &&
	      slide->cache_foreground->width == width &&
	      slide->cache_foreground->height == height))
		{
			free(slide->cache_foreground);
			slide->cache_foreground = new_asciibuffer(width, height);
			dirty = true;
			render_ssim(slide->cache_foreground, slide->image_foreground, "");
		}

	free(slide->cache_dialog);
	slide->cache_dialog = new_asciibuffer(width, height);
	render_dialogs(slide->cache_dialog,
	               slide->message,
	               slide->dialogs,
	               slide->dialogs_count,
	               choice);

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
		.height = 0,
		.choice = 0
	};

	return context;
}

int
slides_loop(struct slide_context *context, struct event event)
{
	switch (event.tag)
		{
		case UP:
			if (context->choice > 0)
				--context->choice;
			break;
		case DOWN:
			if (context->choice < context->current->dialogs_count - 1)
				++context->choice;
			break;
		case RET:
			context->current = context->current->dialogs[context->choice]->next;
		case CHAR:
			if (event.character == 'q') return 1;
		}

	size_t width  = get_terminal_width();
	size_t height = get_terminal_height();
	render_slides(context->current,
	              context->choice,
	              width  == 0 ? 64 : width,
	              height == 0 ? 32 : height);
	show_asciibuffer(context->current->cache_composed);
	return 0;
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
		.cache_composed = NULL,
		.cache_dialog = NULL,
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

void
free_slide(struct slide *slide)
{
	free(slide->message);
	if (slide->cache_background != NULL) free(slide->cache_background);
	if (slide->cache_foreground != NULL) free(slide->cache_foreground);
	if (slide->cache_composed != NULL) free(slide->cache_composed);
	if (slide->cache_dialog != NULL) free(slide->cache_dialog);
	free(slide);
}
