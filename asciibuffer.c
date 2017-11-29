#include "asciibuffer.h"
#include<stdlib.h>
#include<string.h>

struct asciibuffer *new_asciibuffer(size_t width, size_t height)
{
  struct asciibuffer *asciibuffer = malloc(sizeof(struct asciibuffer) + width*height);

  *asciibuffer = (struct asciibuffer) {
    .height = height,
    .width = width,
    .buffer = asciibuffer->in_buffer
  };
  memset(asciibuffer->in_buffer, 0, width*height);
  
  return asciibuffer;
}

void flatten(struct asciibuffer *asciibuffer)
{
  for (int i = 0; i < asciibuffer->height * asciibuffer->width; ++i)
    if (asciibuffer->buffer[i] == '\0')
      asciibuffer->buffer[i] = ' ';
}

void clear(struct asciibuffer *asciibuffer)
{
  memset(asciibuffer->buffer, 0, asciibuffer->height * asciibuffer->width);
}
