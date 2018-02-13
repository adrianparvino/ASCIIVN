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

#ifndef DIALOG_H
#define DIALOG_H

#include "asciibuffer.h"
#include "imagebuffer.h"

struct dialog
{
	struct slide *next;
	char *message;
	char in_message[];
};

size_t
render_dialogs(struct asciibuffer *asciibuffer,
               char *message,
               struct dialog *dialogs[],
               size_t dialogs_count,
               size_t option);

struct dialog *
make_dialog(struct slide *next,
            char *message);

#endif
