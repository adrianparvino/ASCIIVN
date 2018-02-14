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
	// First batch is to fill old
	for (;
	     i < (*context)->fill_start;
	     ++i)
		{
			if ((*context)->fills[i] == NULL)
				{
					(*context)->old->dialogs[i]->next = (*context)->current;
				}
			else
				{
					string_map_append_slide_next_ptr(&(*context)->map,
					                                 (*context)->fills[i],
					                                 &(*context)->old->dialogs[i]->next);
				}
		}
	// If dialog is empty then it is linear.
	if (i == 0 && (*context)->old != NULL)
		{
			(*context)->old->next = (*context)->current;
		}
	
	// Twice old is cleared
	size_t fills_start = i;
	size_t fills_length = 0;
	while ((*context)->fills[fills_start] != EOS)
		{
			(*context)->fills[fills_length++] = (*context)->fills[fills_start++];
		}

	struct slide ***fills;
	if ((fills = string_map_index_slide_next_ptr((*context)->map, (*context)->old_fill_scene)) != NULL)
		{
			for(;
			    *fills != NULL;
			    ++fills)
				{
					**fills = (*context)->current;
				}
		}

	(*context)->fill_start = fills_length;
	(*context)->fills[fills_length] = EOS;
	
	(*context)->old = (*context)->current;
	(*context)->current = slide;
	(*context)->old_fill_scene = (*context)->fill_scene;
	(*context)->fill_scene = NULL;
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
	                   ((*context)->fill_start + i + 2)*sizeof *(*context)->fills);
	(*context)->fills[(*context)->fill_start + i  ] = scene;
	(*context)->fills[(*context)->fill_start + i+1] = EOS;
}

struct slide_builder_context *
slide_builder_init(struct imagebuffer *image_background,
                   struct imagebuffer *image_foreground,
                   char *message)
{
	struct slide_builder_context *context = malloc(sizeof *context +
	                                               sizeof *context->fills);
	struct slide *slide =
		make_slide(image_background,
		           image_foreground,
		           message,
		           NULL,
		           0);

	*context = (struct slide_builder_context) {
		.old = NULL,
		.current = slide,
		.root = slide,
		.map = NULL,
		.fill_scene = NULL,
		.old_fill_scene = NULL,
		.fill_start = 0
	};
	context->fills[0] = EOS;
	// 2 arrays in one

	return context;
}

struct slide *
slide_builder_end(struct slide_builder_context *context)
{
	struct slide *root = context->root;

	size_t i = 0;
	// First batch is to fill old
	for (;
	     i < context->fill_start;
	     ++i)
		{
			if (context->fills[i] == NULL)
				{
					context->old->dialogs[i]->next = context->current;
				}
			else
				{
					string_map_append_slide_next_ptr(&context->map,
					                                 context->fills[i],
					                                 &context->old->dialogs[i]->next);
				}
		}
	// If dialog is empty then it is linear.
	if (i == 0 && context->old != NULL)
		{
			context->old->next = context->current;
		}
	size_t j = i;
	for (;
	     context->fills[j] != EOS;
	     ++j)
		{
			if (context->fills[i] == NULL && context->current != NULL)
				{
					context->current->dialogs[i]->next = NULL;
				}
		}
	// If dialog is empty then it is linear.
	if (i == j)
		{
			context->current->next = NULL;
		}

	struct slide ***fills;
	if ((fills = string_map_index_slide_next_ptr(context->map, context->old_fill_scene)) != NULL)
		{
			for(;
			    *fills != NULL;
			    ++fills)
				{
					**fills = context->current;
				}
		}
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
