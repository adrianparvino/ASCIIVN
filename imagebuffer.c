#include "imagebuffer.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<png.h>

struct imagebuffer *new_imagebuffer(size_t width, size_t height)
{
  struct imagebuffer *imagebuffer = malloc(sizeof(struct imagebuffer) + width*height);

  *imagebuffer = (struct imagebuffer) {
    .width = width,
    .height = height,
    .buffer = imagebuffer->in_buffer
  };
  memset(imagebuffer->in_buffer, 0, width*height);
  
  return imagebuffer;
}

struct imagebuffer *load_imagebuffer_png(char font[])
{
  FILE *png_file = fopen(font, "rb");
  
  if (png_file == NULL)
    {
      exit(1); // TODO: Error handling
    }
  
  unsigned char header[8];
  
  if (fread(header, 1, sizeof(header), png_file) != sizeof(header))
    {
      exit(1);
    }
  if (png_sig_cmp(header, 0, sizeof(header)))
    {
      exit(1); /// TODO: Error handling
    }
  
  png_structp png_ptr =
    png_create_read_struct(PNG_LIBPNG_VER_STRING,
                           NULL, NULL, NULL);
  if (!png_ptr)
    {
      exit(1);
    }
  
  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr)
    {
      png_destroy_read_struct(&png_ptr, NULL, NULL);
      exit(1);
    }
  
  png_infop end_info = png_create_info_struct(png_ptr);
  if (!end_info)
    {
      png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
      exit(1);
    }
  
  if (setjmp(png_jmpbuf(png_ptr)))
    {
      png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
      fclose(png_file);
      exit(1);
    }
  
  png_init_io(png_ptr, png_file);
  png_set_sig_bytes(png_ptr, sizeof(header));
    
  fclose(png_file);
}
