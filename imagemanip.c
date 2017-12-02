#include <assert.h>
#include "imagemanip.h"

#define trunc(x, n) ((x) > (n) ? (n) : (x))
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

  return imagebuffer;
}

struct imagebuffer *top_bottom(struct imagebuffer *x,
                               struct imagebuffer *y)
{
  assert(x->width == y->width);

  int height = (x->height + y->height);

  struct imagebuffer *imagebuffer = new_imagebuffer(x->width, height);

  int i;
  for (i = 0; i < x->width * x->height; ++i)
    {
      imagebuffer->buffer[i] = x->buffer[i];
    }
  
  for (int j = 0; i < x->width * height; ++i, ++j)
    {
      imagebuffer->buffer[i] = y->buffer[j];
    }
  
  return imagebuffer;
}

void *scale_nearest(struct imagebuffer *dest,
                    struct imagebuffer *src)
{
  for (int i = 0; i < dest->height * dest->width; ++i)
    {
      
      size_t x = (i % dest->width) * src->width / dest->width;
      size_t y = (i / dest->width) * src->height / dest->height;
      dest->buffer[i] = src->buffer[y*(src->width) + x];
    }
}

/* NB: Probably Broken Implementation */
void *scale_bilinear(struct imagebuffer *dest,
                     struct imagebuffer *src)
{
  for (int i = 0; i < dest->height * dest->width; ++i)
    {
      
      float x = ((float) (i % dest->width)) * src->width / dest->width;
      float y = ((float) (i / dest->width)) * src->height / dest->height;

      double xi, yi;
      float xf = modf(x, &xi),
            yf = modf(y, &yi);

      dest->buffer[i] = src->buffer[(int) (yi*(src->width) + xi)]*(1 - yf)*(1 - xf)
                      + src->buffer[(int) (yi*(src->width) + trunc(xi + 1, src->width - 1))]*(1 - yf)*xf
                      + src->buffer[(int) (trunc(yi + 1, src->height - 1)*(src->width) + xi)]*yf*(1 - xf)
                      + src->buffer[(int) (trunc(yi + 1, src->height - 1)*(src->width) + trunc(xi + 1, src->width - 1))]*yf*xf;
    }
}
