#ifndef ASCII_BUFFER_FILL_H
#define ASCII_BUFFER_FILL_H

#include "asciibuffer.h"

int render_fill(struct asciibuffer *dest,
                unsigned char *source,
                size_t width, size_t height);
#endif
