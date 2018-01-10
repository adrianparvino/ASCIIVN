#ifndef IMAGEMANIP_KERNEL_H
#define IMAGEMANIP_KERNEL_H

#include <stddef.h>
#include "imagebuffer.h"

void
scale_bilinear_prepare(unsigned char *
                       (*index)(struct imagebuffer *image,
                                size_t x,
                                size_t y),
                       unsigned char      *out_x0y0,
                       unsigned char      *out_x0y1,
                       unsigned char      *out_x1y0,
                       unsigned char      *out_x1y1,
                       float              *out_xf,
                       float              *out_yf,
                            
                       struct imagebuffer *dest,
                       struct imagebuffer *src,
                            
                       float               stepx,
                       float               stepy);


static inline void
scale_bilinear_kernel(unsigned char *in_x0y0,
                      unsigned char *in_x0y1,
                      unsigned char *in_x1y0,
                      unsigned char *in_x1y1,
                                         
                      float *in_xf,
                      float *in_yf,

                      size_t n,
                                         
                      unsigned char *out)
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
