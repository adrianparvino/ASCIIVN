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
                       size_t               height)
{
	size_t stepx = src->width  - 2;
	size_t stepy = src->height - 2;
	
	size_t yerror = 0;
	size_t yi = 0;
	for (size_t k = 0, j = 0; j < height; ++j, yerror += stepy)
		{
			while (yerror >= height - 1)
				{
					yerror -= height - 1;
					++yi;
				}
			
			size_t xerror = 0;
			size_t xi = 0;
			for (size_t i = 0; i < width; ++i, ++k, xerror += stepx)
				{
					while (xerror >= width - 1)
						{
							xerror -= width - 1;
							++xi;
						}
					
					const size_t xi_ = xi + 1;
					const size_t yi_ = yi + 1;

					out_xf[k] = xerror;
					out_yf[k] = yerror;

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
