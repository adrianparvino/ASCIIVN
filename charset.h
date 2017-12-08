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

  size_t n;
  struct chardesc characters[];
};

struct charset* generate_test_charset();
struct charset* generate_test_charset_ssim();
void free_charset(struct charset* charset);

#endif
