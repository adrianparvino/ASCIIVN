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

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "asciibufferfill.h"
#include "asciibufferssim.h"
#include "charset.h"
#include "xbmutils.h"
#include "imagemanip.h"
#include "testimage.h"
#include "event.h"
#include "dialog.h"
#include "slides.h"
#include "slidebuilder.h"

#define LENGTH(x) (sizeof x / sizeof *x)
int
main(int argc, char *argv[])
{
	bool benchmark = false;
	for (size_t i = 1; i < argc; ++i)
		{
			benchmark = benchmark || strcmp(argv[i], "--benchmark") == 0;
		}
	
	struct imagebuffer *wae = new_imagebuffer_from_png("wae.png");
	struct imagebuffer *dog = new_imagebuffer_from_png("dog.png");
	struct imagebuffer *dog_bg = new_imagebuffer_from_png("dog-background.png");

	struct dialog *dialogs[] = {
		make_dialog(make_slide(dog_bg, dog, "", NULL, 0), "Yes"),
		make_dialog(make_slide(dog_bg, dog, "", NULL, 0), "No"),
	};

	struct slide *initial_slide =
		make_slide(dog_bg, wae, "Do you know the wae?", dialogs, LENGTH(dialogs));

	struct event event;
	event_start();
	struct slide_context *context =
		slides_init(initial_slide);
	event = (struct event) { .tag = NONE };
	if (benchmark)
		{
			slides_loop(context, event);
			event = (struct event) { .tag = RET };
			slides_loop(context, event);
			goto end;
		}
	for (;;)
		{
			if (slides_loop(context, event) == 1) break;
			event = event_getevent();
		}
 end:
	slides_end(context);
	event_end();

	for (size_t i = 0; i < LENGTH(dialogs); ++i)
		{
			free_slide(dialogs[i]->next);
			free(dialogs[i]);
		}
	
	free_slide(initial_slide);

	free(dog_bg);
	free(wae);
	free(dog);
	
	return 0;
}
