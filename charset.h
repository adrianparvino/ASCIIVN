#ifndef ASCII_CHARSET_H
#define ASCII_CHARSET_H

#include<stddef.h>

struct chardesc
{
  char character;
  
  unsigned char *glyph;
};

struct charset
{
  size_t width, height;

  struct chardesc characters[];
};

struct charset* generate_test_charset(size_t *chardescs);
struct charset* generate_test_charset_ssim(size_t *chardescs);
void free_charset(struct charset* charset, size_t chardescs);

#endif
