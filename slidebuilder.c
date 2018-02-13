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

#include "slides.h"
#include "dialog.h"
#include "slidebuilder.h"
#include "stringmap.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>

void 
slide_builder_scene(struct slide_builder_context **context,
                         char *name)
{
	(*context)->fills = string_map_index((*context)->map, name);
}

void 
slide_builder_slide(struct slide_builder_context **context,
                          struct imagebuffer *image_background,
                          struct imagebuffer *image_foreground,
                          char *message)
{

	struct slide *slide =
		make_slide(image_background,
		           image_foreground,
		           message,
		           NULL,
		           0);

	for (struct slide ***fill = (*context)->current_fills;
	     *fill != NULL;
	     ++fill)
		{
			**fill = slide;
		}
	
	if ((*context)->fills != NULL)
		{
			for(struct slide ***fill = (*context)->fills;
			    *fill != NULL;
			    ++fill)
				{
			    **fill = slide;
				}

		}
	(*context)->fills = NULL;
	(*context)->current = slide;
	
	(*context)->current_fills[0] = &slide->next;
	(*context)->current_fills[1] = NULL;
}

void 
slide_builder_slide_reply(struct slide_builder_context **context,
                          char *reply,
                          char *scene)
{
	if ((*context)->current_fills[0] == &(*context)->current->next)
		{
			(*context)->current_fills[0] = NULL;
		}

	(*context)->current = realloc((*context)->current,
	                              sizeof *(*context)->current + 
	                              ((*context)->current->dialogs_count + 1)*
	                              sizeof *(*context)->current->dialogs);

	struct dialog *dialog = make_dialog(NULL, reply);
	(*context)->current->dialogs[(*context)->current->dialogs_count++] = dialog;
	
	if (scene != NULL)
		{
			string_map_append(&(*context)->map,
			                  scene,
			                  &dialog->next);
		}
	else
		{
			// HOLY SHIT. FUCK REALLOC.
			size_t i = 0;
			for(struct slide ***slides = (*context)->current_fills;
			    *slides != NULL;
			    ++slides, ++i);
			*context = realloc(*context,
			                   sizeof **context +
			                   (i + 2)*sizeof *(*context)->current_fills);
			(*context)->current_fills[i] = &dialog->next;
			(*context)->current_fills[i+1] = NULL;
		}
	(*context)->current->dialogs_count++;
}

struct slide_builder_context *
slide_builder_init(struct imagebuffer *image_background,
                   struct imagebuffer *image_foreground,
                   char *message)
{
	struct slide_builder_context *context = malloc(sizeof *context +
	                                               2*sizeof *context->current_fills);
	*context = (struct slide_builder_context) {
		.map = NULL,
		.fills = NULL,
	};
	context->current_fills[0] = NULL;

	slide_builder_slide(&context,
	                    image_background,
	                    image_foreground,
	                    message);
	context->root = context->current;

	return context;
}
 
struct slide *
slide_builder_end(struct slide_builder_context *context)
{
	struct slide *root = context->root;
	
	for (struct slide ***fill = context->current_fills;
	     *fill != NULL;
	     ++fill)
		{
			**fill = root;
		}
	
	if (context->fills != NULL)
		{
			for(struct slide ***fill = context->fills;
			    *fill != NULL;
			    ++fill)
				{
			    **fill = root;
				}

		}
	
	free(context);
	return root;
}
