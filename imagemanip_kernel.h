#ifndef IMAGEMANIP_KERNEL_H
#define IMAGEMANIP_KERNEL_H

#include <stddef.h>
#include "imagebuffer.h"
#include "imagemanip_kernel.h"

void
scale_bilinear_prepare(unsigned char *
                       (*index)(const struct imagebuffer *image,
                                size_t x,
                                size_t y),
                       unsigned char      *restrict out_x0y0,
                       unsigned char      *restrict out_x0y1,
                       unsigned char      *restrict out_x1y0,
                       unsigned char      *restrict out_x1y1,
                       size_t             *restrict out_xf,
                       size_t             *restrict out_yf,
                            
                       const struct imagebuffer *src,
                            
                       size_t               width,
                       size_t               height);


void
scale_bilinear_store(unsigned char *
                     (*index)(const struct imagebuffer *image,
                              size_t x,
                              size_t y),
                     const unsigned char *in,
                     struct imagebuffer *dest);

static inline void
scale_bilinear_kernel(const unsigned char *restrict in_x0y0,
                      const unsigned char *restrict in_x0y1,
                      const unsigned char *restrict in_x1y0,
                      const unsigned char *restrict in_x1y1,
                                         
                      const size_t *restrict in_xf,
                      const size_t *restrict in_yf,

                      size_t width,
                      size_t height,
                                         
                      unsigned char * restrict out)
{
	for (size_t i = 0; i < width * height; ++i)
		{
			out[i] =
				in_x0y0[i]*(1 - (float) in_xf[i]/(width - 1))*(1 - (float) in_yf[i]/(height - 1)) +
				in_x0y1[i]*     (float) in_xf[i]/(width - 1) *(1 - (float) in_yf[i]/(height - 1)) +
				in_x1y0[i]*(1 - (float) in_xf[i]/(width - 1))*     (float) in_yf[i]/(height - 1)  +
				in_x1y1[i]*     (float) in_xf[i]/(width - 1) *     (float) in_yf[i]/(height - 1)  ;
		}
}

#endif
