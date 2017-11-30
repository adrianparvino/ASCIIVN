#ifndef IMAGEMANIP_H
#define IMAGEMANIP_H

#include "imagebuffer.h"
struct imagebuffer *side_by_side(struct imagebuffer *x,
                                 struct imagebuffer *y);
struct imagebuffer *top_bottom(struct imagebuffer *x,
                               struct imagebuffer *y);

void *scale_nearest(struct imagebuffer *dest,
                    struct imagebuffer *src);

void *scale_bilinear(struct imagebuffer *dest,
                     struct imagebuffer *src);

#endif
