#ifndef ASCII_BUFFER_FILL_H
#define ASCII_BUFFER_FILL_H

#include "imagebuffer.h"
#include "asciibuffer.h"

void render_fill(struct asciibuffer *dest,
                 struct imagebuffer *src,
                 char fontname[]);
#endif
