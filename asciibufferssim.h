#ifndef ASCII_BUFFER_SSIM_H
#define ASCII_BUFFER_SSIM_H

#include "asciibuffer.h"


int render_ssim(struct asciibuffer *dest,
                unsigned char *source,
                size_t width, size_t height,
                char fontname[]);

#endif
