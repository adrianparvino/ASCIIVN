#include "asciibuffer.h"
#include<stdlib.h>
#include<string.h>

struct asciibuffer *new_asciibuffer(size_t width, size_t height)
{
  struct asciibuffer *asciibuffer = malloc(sizeof(asciibuffer) + width*height);
  asciibuffer->size = width*height;
  asciibuffer->width = width;
  memset(&asciibuffer->buffer, 0, width*height);
  
  return asciibuffer;
}

void flatten(struct asciibuffer *asciibuffer)
{
  for (int i = 0; i < asciibuffer->size; ++i)
    if (asciibuffer->buffer[i] == '\0')
      asciibuffer->buffer[i] = ' ';
}

void clear(struct asciibuffer *asciibuffer)
{
  memset(asciibuffer->buffer, 0, asciibuffer->size);
}
