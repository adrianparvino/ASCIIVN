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

#include "xbmutils.h"

#include "fonts/FixedsysExcelsior/slash.xbm"
#include "fonts/FixedsysExcelsior/backslash.xbm"
#include "fonts/FixedsysExcelsior/pipe.xbm"
#include "fonts/FixedsysExcelsior/dot.xbm"
#include "fonts/FixedsysExcelsior/comma.xbm"
#include "fonts/FixedsysExcelsior/dollar.xbm"

unsigned char smiley[8][8] = {
  { 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00 },
  { 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff },
  { 0xff, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0xff },
  { 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff },
  { 0xff, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0xff },
  { 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff },
  { 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff },
  { 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00 }
};

unsigned char half_smiley[64] = {
  0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
  0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00,
  0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00
};


unsigned char smiley_flat[64] = {
  0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
  0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
  0xff, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0xff,
  0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
  0xff, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0xff,
  0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff,
  0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
  0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00
};

unsigned char blank[8][8] = {
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 }
};

unsigned char *test_slash()
{
  return xbm_to_unsigned_char_arr(slash_bits, slash_width, slash_height);
}

unsigned char *test_backslash()
{
  return xbm_to_unsigned_char_arr(backslash_bits, backslash_width, backslash_height);
}

unsigned char *test_pipe()
{
  return xbm_to_unsigned_char_arr(pipe_bits, pipe_width, pipe_height);
}

unsigned char *test_dot()
{
  return xbm_to_unsigned_char_arr(dot_bits, dot_width, dot_height);
}
unsigned char *test_comma()
{
  return xbm_to_unsigned_char_arr(comma_bits, comma_width, comma_height);
}
unsigned char *test_dollar()
{
  return xbm_to_unsigned_char_arr(dollar_bits, dollar_width, dollar_height);
}
