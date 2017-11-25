#include "asciibufferfill.h"

int render_fill(struct asciibuffer *dest,
                unsigned char *source,
                size_t width, size_t height)
{
  for (int i = 0; i < dest->size; ++i)
    {
      int x = (i % dest->width) * width / dest->width;
      int y = (i / dest->width) * height / (dest->size/dest->width);
      dest->buffer[i] = (source[y*width + x] > 128) ? '$' : ' ';
    }
}
