#ifndef IMAGE_BUFFER_H
#define IMAGE_BUFFER_H

#include <stddef.h>

struct imagebuffer {
  size_t width, height;
  unsigned char *buffer;
  unsigned char in_buffer[];
};

struct imagebuffer *new_imagebuffer(size_t width, size_t height);
struct imagebuffer *new_imagebuffer_from_png(char image_name[]);

#endif
