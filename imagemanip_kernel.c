#include "imagemanip_kernel.h"

void scale_bilinear_prepare(unsigned char *(*index)(struct imagebuffer *image,
                                                    size_t x,
                                                    size_t y),
                            unsigned char      *in_x0y0,
                            unsigned char      *in_x0y1,
                            unsigned char      *in_x1y0,
                            unsigned char      *in_x1y1,
                            float              *in_xf,
                            float              *in_yf,
                            
                            struct imagebuffer *dest,
                            struct imagebuffer *src,
                            
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

					in_xf[k] = x;
					in_yf[k] = y;

					in_x0y0[k] = (*index(src, xi , yi ));
					in_x1y0[k] = (*index(src, xi_, yi ));
					in_x0y1[k] = (*index(src, xi , yi_));
					in_x1y1[k] = (*index(src, xi_, yi_));
				}
		}
}
