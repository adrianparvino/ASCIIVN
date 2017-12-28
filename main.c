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

#include<stdio.h>
#include<stdlib.h>
#include"asciibufferfill.h"
#include"asciibufferssim.h"
#include"charset.h"
#include"xbmutils.h"
#include"imagemanip.h"
#include"testimage.h"
#include "keyevent.h"

int
main()
{
	int caretwidth = 256;
	int caretheight = 64;

	struct asciibuffer *asciibuffer = new_asciibuffer(caretwidth, caretheight);
	struct asciibuffer *asciibuffer2 = new_asciibuffer(caretwidth, caretheight);

	struct charset *charset =
		charset_read_from_directory("./fonts/Monaco-10");
	
	struct imagebuffer *dog = new_imagebuffer_from_png("christmas-anime-lineart.png");
	struct imagebuffer *dog2 =
		new_imagebuffer(caretwidth * charset->width, caretheight * charset->height);
	
	scale_bilinear(dog2, dog);

	// DEBUGGING REMOVE
	render_ssim_charset_unsafe(asciibuffer2, dog2, charset);
	flatten(asciibuffer2);
	show_asciibuffer(asciibuffer2);

	free(asciibuffer);
	free(asciibuffer2);

	free_charset(charset);
	free(dog2);
	free(dog);
	
	return 0;
	// DEBUGGING REMOVE

	keyevent_start();
	
	for (struct keyevent keyevent = keyevent_getenvent();
	     keyevent.tag == CHAR && keyevent.character != 'e';
	     keyevent = keyevent_getenvent())
		{
			switch (keyevent.tag)
				{
				case CHAR:
					switch (keyevent.character)
						{
							case 'q':
								render_fill(asciibuffer, dog, "");
								flatten(asciibuffer);
								show_asciibuffer(asciibuffer);
								break;
							case 'w':
								render_ssim_charset_unsafe(asciibuffer2, dog2, charset);
								flatten(asciibuffer2);
								show_asciibuffer(asciibuffer2);
								break;
						}
				}
		}

	free(asciibuffer);
	free(asciibuffer2);

	free_charset(charset);
	free(dog2);
	free(dog);

	return 0;
}
