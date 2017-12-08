#ifndef ASCII_BUFFER_SSIM_H
#define ASCII_BUFFER_SSIM_H

#include "asciibuffer.h"
#include "imagebuffer.h"
#include "charset.h"

int render_ssim(struct asciibuffer *dest,
                struct imagebuffer *source,
                char fontname[]);

int render_ssim_charset_unsafe(struct asciibuffer *dest,
                               struct imagebuffer *source,
                               struct charset *font_charset);

float ssim_imagebuffer(size_t column_offset,
                       size_t row_offset,
                       struct imagebuffer *x,
                       struct imagebuffer *y);

#endif
