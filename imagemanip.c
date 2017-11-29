#include <assert.h>
#include "imagemanip.h"

struct imagebuffer *side_by_side(struct imagebuffer *x,
                                 struct imagebuffer *y)
{
  assert(x->height == y->height);

  int width = (x->width + y->width);

  struct imagebuffer *imagebuffer = new_imagebuffer(width, x->height);
  
  for (int i = 0; i < x->height; ++i)
    {
      for (int j = 0; j < x->width; ++j)
        {
          imagebuffer->buffer[i*width + j] = x->buffer[i*x->width + j];
        }
    }
  
  for (int i = 0; i < y->height; ++i)
    {
      for (int j = 0; j < y->width; ++j)
        {
          imagebuffer->buffer[i*width + j + x->width] = y->buffer[i*y->width + j];
        }
    }
}
