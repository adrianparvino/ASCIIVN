#include "imagebuffer.h"

struct imagebuffer *new_imagebuffer(size_t width, size_t height)
{
  struct imagebuffer *imagebuffer = malloc(sizeof(struct imagebuffer) + width*height);

  *imagebuffer = (struct imagebuffer) {
    .height = height,
    .width = width,
    .buffer = imagebuffer->in_buffer
  };
  memset(imagebuffer->in_buffer, 0, width*height);
  
  return imagebuffer;
}
