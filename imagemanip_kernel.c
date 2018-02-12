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
                       float               stepy)
{
	float y = 0;
	float yi = 0;
	for (size_t k = 0, j = 0; j < dest->height; ++j, y += stepy)
		{
			while (y >= 1)
				{
					++yi;
					--y;
				}
			
			float x = 0;
			float xi = 0;
			for (size_t i = 0; i < dest->width; ++i, ++k, x += stepx)
				{
					while (x >= 1)
						{
							++xi;
							--x;
						}
					
					const float xi_ = xi + 1;
					const float yi_ = yi + 1;

					out_xf[k] = x;
					out_yf[k] = y;

					out_x0y0[k] = (*index(src, xi , yi ));
					out_x1y0[k] = (*index(src, xi_, yi ));
					out_x0y1[k] = (*index(src, xi , yi_));
					out_x1y1[k] = (*index(src, xi_, yi_));
				}
		}
}


void
scale_bilinear_store(unsigned char *
                     (*index)(const struct imagebuffer *image,
                              size_t x,
                              size_t y),
                     const unsigned char *in,
                     struct imagebuffer *dest)
{
	
	for (size_t j = 0; j < dest->height; ++j)
		{
			for (size_t i = 0; i < dest->width; ++i)
				{
					*index(dest, i, j) = in[j*dest->width + i];
				}
		}
}
