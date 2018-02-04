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
#include "slidebuilder.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>

void slides_builder_scene(struct slide_builder_context *context,
                         char *name)
{
	context->fills = (struct slide ***) string_map_index(context->map, name);
}

void slides_builder_slide(struct slide_builder_context *context,
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

	for (struct slide ***fill = context->current_fills;
	     *fill != EOV && *fill != NULL;
	     ++fill)
		{
			*fill = &slide;
		}
	
	if (context->fills != NULL)
		{
			for(struct slide ***fill = context->fills;
			    *fill != NULL && *fill != EOV;
			    ++fill)
				{
			    *fill = &slide;
				}
		}
	
	context->current_fills[0] = &slide->next;
	context->current_fills[1] = NULL;
}
