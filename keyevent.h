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

#ifndef KEYEVENT_H
#define KEYEVENT_H

enum KEYEVENT_TAG {
	UP = 'A',
	DOWN = 'B',
	CHAR
};

struct keyevent {
	enum KEYEVENT_TAG tag;
	char character;
};
	
void keyevent_start();
struct keyevent keyevent_getevent();
void keyevent_end();

#endif
