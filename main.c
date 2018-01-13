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
#include <stdlib.h>
#include "asciibufferfill.h"
#include "asciibufferssim.h"
#include "charset.h"
#include "xbmutils.h"
#include "imagemanip.h"
#include "testimage.h"
#include "keyevent.h"
#include "dialog.h"
#include "slides.h"

#define LENGTH(x) (sizeof x / sizeof *x)
int
main()
{
	int caretwidth = 32;
	int caretheight = 16;

	struct charset *charset =
		charset_read_from_directory("./fonts/Monaco-10");
	
	struct imagebuffer *wae = new_imagebuffer_from_png("wae.png");
	struct imagebuffer *dog = new_imagebuffer_from_png("dog.png");
	assert(dog->pixel_size == 2);
	struct imagebuffer *dog_bg = new_imagebuffer_from_png("dog-background.png");
	assert(dog_bg->pixel_size == 2);
	struct imagebuffer *dog_scaled =
		new_imagebuffer(caretwidth * charset->width, caretheight * charset->height);
	struct imagebuffer *wae_scaled =
		new_imagebuffer(caretwidth * charset->width, caretheight * charset->height);
	struct imagebuffer *dog_bg_scaled =
		new_imagebuffer(caretwidth * charset->width, caretheight * charset->height);
	
	scale_bilinear(dog_scaled, dog);
	scale_bilinear(wae_scaled, wae);
	scale_bilinear(dog_bg_scaled, dog_bg);

	struct asciibuffer *asciibuffer = new_asciibuffer_alpha(caretwidth, caretheight);
	struct asciibuffer *asciibuffer_bg = new_asciibuffer(caretwidth, caretheight);

	struct dialog *dialogs[] = {
		make_dialog(make_slide(dog_bg_scaled, wae_scaled, "", NULL, 0), "Yes"),
		make_dialog(make_slide(dog_bg_scaled, wae_scaled, "", NULL, 0), "No"),
	};

	struct slide *initial_slide =
		make_slide(dog_bg_scaled, wae_scaled, "Do you know the wae?", dialogs, LENGTH(dialogs));

	struct keyevent keyevent;
	keyevent_start();
	for (;;)
		{
			keyevent = keyevent_getevent();
			switch (keyevent.tag)
				{
				case UP:
					render_slides(initial_slide, caretwidth, caretheight);
					show_asciibuffer(initial_slide->cache_composed);
					break;
				case DOWN:
					render_ssim_charset_unsafe(asciibuffer, dog_scaled, charset);
					render_fill(asciibuffer_bg, dog_bg_scaled, "");
					compose((struct imagebuffer *) asciibuffer_bg,
					        (struct imagebuffer *) asciibuffer, 0 ,0);
					flatten(asciibuffer_bg);
					show_asciibuffer(asciibuffer_bg);
					break;
				case CHAR:
					if (keyevent.character == 'q') goto end;
					break;
				}
		}
 end:
	keyevent_end();

	for (size_t i = 0; i < LENGTH(dialogs); ++i)
		{
			free_slide(dialogs[i]->next);
			free(dialogs[i]);
		}
	
	free_slide(initial_slide);

	free(asciibuffer_bg);
	free(asciibuffer);

	free(dog_bg_scaled);
	free(dog_scaled);
	free(wae_scaled);

	free(dog_bg);
	free(wae);
	free(dog);
	
	free_charset(charset);
	
	return 0;
}
