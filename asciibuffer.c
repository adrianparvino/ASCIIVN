#include "asciibuffer.h"

#include<stdio.h>
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
  for (size_t i = 0; i < asciibuffer->height * asciibuffer->width; ++i)
    if (asciibuffer->buffer[i] == '\0')
      asciibuffer->buffer[i] = ' ';
}

void clear(struct asciibuffer *asciibuffer)
{
  memset(asciibuffer->buffer, 0, asciibuffer->height * asciibuffer->width);
}

void show_asciibuffer(struct asciibuffer *asciibuffer)
{
  for (size_t i = 0; i < asciibuffer->height; ++i)
    printf("%.*s\n", (int) asciibuffer->width, asciibuffer->buffer + i*asciibuffer->width);
}
