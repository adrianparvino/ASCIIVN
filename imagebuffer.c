/* This file is part of ASCIIVN.
 *
 * Copyright (C) 2017  Adrian Parvin D. Ouano
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <png.h>

#include "imagebuffer.h"

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

struct imagebuffer *new_imagebuffer_from_png(char image_name[])
{
  FILE *image_file = fopen(image_name, "rb");
  if (image_file == NULL)
    {
      exit(1);
    }

  png_byte header[8];
  
  if (fread(header, sizeof(*header), sizeof(header), image_file) < sizeof(header))
    {
      fclose(image_file);
      exit(1);
    }

  if (png_sig_cmp(header, 0, sizeof(header)))
    {
      fclose(image_file);
      exit(1);
    }

  png_structp png_ptr = png_create_read_struct
    (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  
  if (!png_ptr)
    {
      fclose(image_file);
      exit(1);
    }
  
  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr)
    {
      png_destroy_read_struct(&png_ptr, NULL, NULL);

      fclose(image_file);
      exit(1);
    }
  
  //   png_infop end_info = png_create_info_struct(png_ptr);
  //   if (!end_info)
  //     {
  //       png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
  // 
  //       fclose(image_file);
  //       exit(1);
  //     }

  if (setjmp(png_jmpbuf(png_ptr)))
    {
      png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

      fclose(image_file);
      exit(1);
    }
  
  png_init_io(png_ptr, image_file);
  png_set_sig_bytes(png_ptr, sizeof(header));

  png_read_info(png_ptr, info_ptr);

  png_color_16 *image_background;

  if (!png_get_bKGD(png_ptr, info_ptr, &image_background))
    {
      image_background = &((png_color_16) {
          .index = 255,
            .red = 65535,
            .blue = 65535,
            .green = 65535,
            .gray = 0,
            });
    }
  
  int color_type = png_get_color_type(png_ptr, info_ptr),
      bit_depth = png_get_bit_depth(png_ptr, info_ptr);

  // int number_of_passes = png_set_interlace_handling(png_ptr);

  /* Expand paletted colors into true RGB triplets */
  if (color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_palette_to_rgb(png_ptr);
  /* Expand grayscale images to the full 8 bits from 1, 2, or 4 bits/pixel */
  if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
    png_set_expand_gray_1_2_4_to_8(png_ptr);
  
  if (color_type == PNG_COLOR_TYPE_RGB ||
      color_type == PNG_COLOR_TYPE_RGB_ALPHA)
    {
      png_set_rgb_to_gray(png_ptr, 1, -1, -1);
    }
  png_set_invert_mono(png_ptr);
  
  
  png_set_background(png_ptr, image_background,
                     PNG_BACKGROUND_GAMMA_FILE, 0, 1.0);

  png_read_update_info(png_ptr, info_ptr);
  
  int width = png_get_image_width(png_ptr, info_ptr),
      height = png_get_image_height(png_ptr, info_ptr);
  color_type = png_get_color_type(png_ptr, info_ptr);
  bit_depth = png_get_bit_depth(png_ptr, info_ptr);
  
  assert(png_get_channels(png_ptr, info_ptr) == 1);
  assert(color_type == PNG_COLOR_TYPE_GRAY);
  assert(bit_depth == 8);

  png_bytep row_pointers[height];

  struct imagebuffer *imagebuffer = malloc(sizeof(struct imagebuffer) + width*height);

  *imagebuffer = (struct imagebuffer) {
    .width = width,
    .height = height,
    .buffer = imagebuffer->in_buffer
  };
  
  memset(imagebuffer->in_buffer, 0, width*height);

  int i;
  size_t x;
  for (x = 0, i = 0; i < width*height; ++x, i += width)
    {
      row_pointers[x] = imagebuffer->buffer + i;
    }

  // png_set_rows(png_ptr, info_ptr, row_pointers);
  png_read_image(png_ptr, row_pointers);
  // png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
  /*
  fclose(image_file); */
  
  png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
  fclose(image_file);
  return imagebuffer;
}
