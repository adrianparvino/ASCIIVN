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

#ifndef TEST_IMAGE_H
#define TEST_IMAGE_H

extern unsigned char smiley[8][8];
extern unsigned char half_smiley[64];
extern unsigned char smiley_flat[64];
extern unsigned char blank[8][8];

unsigned char *test_slash();
unsigned char *test_backslash();
unsigned char *test_pipe();
unsigned char *test_dot();
unsigned char *test_comma();
unsigned char *test_dollar();

#endif
