#ifndef ASCII_BUFFER_H
#define ASCII_BUFFER_H

#include<stddef.h>

struct asciibuffer
{
  size_t size, width;
  char buffer[];
};

struct asciibuffer *new_asciibuffer(size_t width, size_t height);
void flatten(struct asciibuffer *asciibuffer);
void clear(struct asciibuffer *asciibuffer);

#endif
