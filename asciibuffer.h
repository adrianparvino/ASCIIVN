#ifndef ASCII_BUFFER_H
#define ASCII_BUFFER_H

#include<stddef.h>

struct asciibuffer
{
  size_t height, width;
  char *buffer;
  char in_buffer[];
};

struct asciibuffer *new_asciibuffer(size_t width, size_t height);
void flatten(struct asciibuffer *asciibuffer);
void clear(struct asciibuffer *asciibuffer);

#endif
