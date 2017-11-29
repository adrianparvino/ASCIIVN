#include <stdlib.h>

#include "charset.h"
#include "testimage.h"

#include "fonts/FixedsysExcelsior/slash.xbm"
#include "fonts/FixedsysExcelsior/backslash.xbm"

struct charset* generate_test_charset(size_t *chardescs)
{
  struct charset *test_charset = malloc(sizeof(struct charset) + 2*sizeof(struct chardesc));
  
  test_charset->width = slash_width;
  test_charset->height = slash_height;
  test_charset->characters[0] = (struct chardesc)
    {
      '/',
      test_slash()
    };
  test_charset->characters[1] = (struct chardesc)
    {
      '\\',
      test_backslash()
    };

  *chardescs = 2;
  return test_charset;
}
