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
                       float              *restrict out_xf,
                       float              *restrict out_yf,
                            
                       const struct imagebuffer *dest,
                       const struct imagebuffer *src,
                            
                       float               stepx,
                       float               stepy);


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
                                         
                      const float *restrict in_xf,
                      const float *restrict in_yf,

                      size_t n,
                                         
                      unsigned char * restrict out)
{
	for (size_t i = 0; i < n; ++i)
		{
			out[i] =
				in_x0y0[i]*(1 - in_xf[i])*(1 - in_yf[i]) +
				in_x0y1[i]*     in_xf[i] *(1 - in_yf[i]) +
				in_x1y0[i]*(1 - in_xf[i])*     in_yf[i]  +
				in_x1y1[i]*     in_xf[i] *     in_yf[i]  ;
		}
}

#endif
