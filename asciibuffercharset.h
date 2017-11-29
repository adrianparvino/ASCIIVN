#ifndef ASCII_BUFFER_CHARSET_H
#define ASCII_BUFFER_CHARSET_H

#include <stddef.h>

struct charset
{
  size_t width, height;
  char (*chars)[];
};
  
#endif
