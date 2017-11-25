#ifndef ASCII_BUFFER_AA_H
#define ASCII_BUFFER_AA_H

#include"asciibuffer.h"

int render_aa(struct asciibuffer *dest,
              unsigned char *source,
              size_t width, size_t height);

#endif
