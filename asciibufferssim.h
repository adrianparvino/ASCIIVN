#ifndef ASCII_BUFFER_SSIM_H
#define ASCII_BUFFER_SSIM_H

#include "asciibuffer.h"


int render_ssim(struct asciibuffer *dest,
                unsigned char *source,
                size_t width, size_t height,
                char fontname[]);

float ssim__unsigned_char(unsigned char n,
			  size_t column_offset,
			  size_t row_offset,
			  size_t row_width,
			  size_t image_width,
			  unsigned char x[n],
			  unsigned char y[n]);

#endif
