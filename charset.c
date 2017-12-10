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

#include <stdlib.h>

#include "charset.h"
#include "testimage.h"

#include "fonts/FixedsysExcelsior/slash.xbm"

struct charset* generate_test_charset()
{
  struct charset *test_charset = malloc(sizeof(struct charset) + 6*sizeof(struct chardesc));
  
  test_charset->width = slash_width;
  test_charset->height = slash_height;

  test_charset->n = 6;
  test_charset->characters[0] = (struct chardesc)
    {
      '\\',
      test_backslash()
    };
  test_charset->characters[1] = (struct chardesc)
    {
      '/',
      test_slash()
    };
  test_charset->characters[2] = (struct chardesc)
    {
      '|',
      test_pipe()
    };
  test_charset->characters[3] = (struct chardesc)
    {
      ',',
      test_comma()
    };
  test_charset->characters[4] = (struct chardesc)
    {
      '.',
      test_dot()
    };
  test_charset->characters[5] = (struct chardesc)
    {
      '$',
      test_dollar()
    };

  return test_charset;
}

struct charset* generate_test_charset_ssim()
{
  struct charset *test_charset = malloc(sizeof(struct charset) + 5*sizeof(struct chardesc));
  
  test_charset->width = slash_width;
  test_charset->height = slash_height;
  
  test_charset->n = 5;
  test_charset->characters[0] = (struct chardesc)
    {
      '\\',
      test_backslash()
    };
  test_charset->characters[1] = (struct chardesc)
    {
      '/',
      test_slash()
    };
  test_charset->characters[2] = (struct chardesc)
    {
      '|',
      test_pipe()
    };
  test_charset->characters[3] = (struct chardesc)
    {
      ',',
      test_comma()
    };
  test_charset->characters[4] = (struct chardesc)
    {
      '.',
      test_dot()
    };

  return test_charset;
}

void free_charset(struct charset* charset)
{
  for (size_t i = 0; i < charset->n; ++i)
    {
      free(charset->characters[i].glyph);
    }
  free(charset);
}
