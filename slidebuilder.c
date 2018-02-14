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

char eos;
#define EOS (&eos)

void
slide_builder_scene(struct slide_builder_context **context,
                    char *name)
{
	(*context)->fill_scene = name;
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

	size_t i = 0;
	for (;
	     (*context)->current_fills[i] != EOS;
	     ++i)
		{
			if ((*context)->current_fills[i] == NULL)
				{
					(*context)->current->dialogs[i]->next = slide;
				}
			else
				{
					string_map_append_slide_next_ptr(&(*context)->map,
					                                 (*context)->current_fills[i],
					                                 &(*context)->current->dialogs[i]->next);
				}
		}
	// If dialog is empty then it is linear.
	if (i == 0)
		{
			(*context)->current->next = slide;
		}

	struct slide ***fills;
	if ((fills = string_map_index_slide_next_ptr((*context)->map, (*context)->fill_scene)) != NULL)
		{
			for(;
			    *fills != NULL;
			    ++fills)
				{
					**fills = slide;
				}
		}

	(*context)->current = slide;
	(*context)->fill_scene = NULL;
	(*context)->current_fills[0] = EOS;
}

void
slide_builder_slide_reply(struct slide_builder_context **context,
                          char *reply,
                          char *scene)
{
	struct dialog *dialog = make_dialog(NULL, reply);
	if ((*context)->root == (*context)->current)
		{
			(*context)->root = (*context)->current = slide_add_dialog((*context)->current, dialog);
		}
	else
		{
			(*context)->current = slide_add_dialog((*context)->current, dialog);
		}

	size_t i = (*context)->current->dialogs_count - 1;
	*context = realloc(*context,
	                   sizeof **context +
	                   (i + 2)*sizeof *(*context)->current_fills);
	(*context)->current_fills[i  ] = scene;
	(*context)->current_fills[i+1] = EOS;
}

struct slide_builder_context *
slide_builder_init(struct imagebuffer *image_background,
                   struct imagebuffer *image_foreground,
                   char *message)
{
	struct slide_builder_context *context = malloc(sizeof *context +
	                                               sizeof *context->current_fills);
	struct slide *slide =
		make_slide(image_background,
		           image_foreground,
		           message,
		           NULL,
		           0);

	*context = (struct slide_builder_context) {
		.current = slide,
		.root = slide,
		.map = NULL,
		.fill_scene = NULL
	};
	context->current_fills[0] = EOS;

	return context;
}

struct slide *
slide_builder_end(struct slide_builder_context *context)
{
	struct slide *root = context->root;

	size_t i = 0;
	for (;
	     context->current_fills[i] != EOS;
	     ++i)
		{
			context->current->dialogs[i]->next = NULL;
		}
	// If dialog is empty then it is linear.
	if (i == 0)
		{
			context->current->next = NULL;
		}

	struct slide ***fills;
	if ((fills = string_map_index_slide_next_ptr(context->map, context->fill_scene)) != NULL)
		{
			for(;
			    *fills != NULL;
			    ++fills)
				{
					**fills = NULL;
				}
		}

	free(context);
	return root;
}
