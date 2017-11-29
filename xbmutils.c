#include "xbmutils.h"

#define rotr8(x) ((x >> 1) | ((x & 1) << 7))

unsigned char *xbm_to_unsigned_char_arr(char *src, size_t width, size_t height)
{
  unsigned char *dest = malloc(width*height);

  size_t i = 0;
  size_t row_index = 0;

  int bytes_per_row = (width + 7)/8; // Number of bytes per row, rounded up
  
  while(i < width*height)
    {
      for (size_t mask = 0x80, column_index = 0;
           column_index < width;
           ++column_index, ++i, mask = rotr8(mask))
        {
          dest[i] = (src[row_index*bytes_per_row + column_index/8] & mask) ? 0xff : 0x00;
        }
      ++row_index;
    }

  return dest;
}
