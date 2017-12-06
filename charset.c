#include <stdlib.h>

#include "charset.h"
#include "testimage.h"

#include "fonts/FixedsysExcelsior/slash.xbm"

struct charset* generate_test_charset(size_t *chardescs)
{
  struct charset *test_charset = malloc(sizeof(struct charset) + 6*sizeof(struct chardesc));
  
  test_charset->width = slash_width;
  test_charset->height = slash_height;
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

  *chardescs = 6;
  return test_charset;
}

struct charset* generate_test_charset_ssim(size_t *chardescs)
{
  struct charset *test_charset = malloc(sizeof(struct charset) + 5*sizeof(struct chardesc));
  
  test_charset->width = slash_width;
  test_charset->height = slash_height;
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

  *chardescs = 5;
  return test_charset;
}

void free_charset(struct charset* charset, size_t chardescs)
{
  for (size_t i = 0; i < chardescs; ++i)
    {
      free(charset->characters[i].glyph);
    }
  free(charset);
}
