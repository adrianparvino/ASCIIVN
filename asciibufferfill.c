#include "asciibufferfill.h"

int render_fill(struct asciibuffer *dest,
                struct imagebuffer *src)
{
  for (int i = 0; i < dest->height * dest->width; ++i)
    {
      size_t x = (i % dest->width) * src->width / dest->width;
      size_t y = (i / dest->width) * src->height / dest->height;
      dest->buffer[i] = (src->buffer[y*(src->width) + x] > 128) ? '$' : ' ';
    }
}
