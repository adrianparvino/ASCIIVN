#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "imagebuffer.h"

struct imagebuffer *new_imagebuffer(size_t width, size_t height)
{
  struct imagebuffer *imagebuffer = malloc(sizeof(struct imagebuffer) + width*height);

  *imagebuffer = (struct imagebuffer) {
    .width = width,
    .height = height,
    .buffer = imagebuffer->in_buffer
  };
  memset(imagebuffer->in_buffer, 0, width*height);
  
  return imagebuffer;
}
