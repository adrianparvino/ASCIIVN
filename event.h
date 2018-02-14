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

#ifndef EVENT_H
#define EVENT_H

enum EVENT_TAG {
	NONE,
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	UP = 72,
	DOWN = 80,
	RET = '\r',
#else
	UP = 'A',
	DOWN = 'B',
	RET = '\n',
#endif
	CHAR,
	RESIZE
};

struct event {
	enum EVENT_TAG tag;
	char character;
};

void event_start();
struct event event_getevent();
void event_end();

#endif
