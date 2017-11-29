#ifndef IMAGE_BUFFER_H
#define IMAGE_BUFFER_H

#include <stddef.h>

struct imagebuffer {
  size_t height, width;
  unsigned char *buffer;
  unsigned char in_buffer[];
};

struct imagebuffer *new_imagebuffer(size_t width, size_t height);

#endif
