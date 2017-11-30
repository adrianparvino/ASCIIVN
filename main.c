#include<stdio.h>
#include<stdlib.h>
#include"asciibufferfill.h"
#include"asciibufferssim.h"
#include"xbmutils.h"
#include"imagemanip.h"
#include"testimage.h"

#include "fonts/FixedsysExcelsior/slash.xbm"
#include "fonts/FixedsysExcelsior/backslash.xbm"

int main()
{
  printf("Hello World!\n");

  int width = backslash_width*16;
  int height = backslash_height;
  
  int caretwidth = 2;
  int caretheight = 2;
  
  struct asciibuffer *asciibuffer = new_asciibuffer(caretwidth, caretheight);
  struct asciibuffer *asciibuffer_2 = new_asciibuffer(caretwidth*9, caretheight*17);

  // render_fill(asciibuffer, smiley_flat, 8, 8);
  struct imagebuffer backslash =
    {
      .height = backslash_height,
      .width = backslash_width,
      .buffer = test_backslash()
    };
  
  struct imagebuffer slash =
    {
      .height = backslash_height,
      .width = backslash_width,
      .buffer = test_slash()
    };

  struct imagebuffer hs =
    {
      .height = 8,
      .width = 8,
      .buffer = half_smiley
    };
  
  struct imagebuffer *caret = side_by_side(&slash, &backslash);
  struct imagebuffer *caret_flip = side_by_side(&backslash, &slash);
  struct imagebuffer *diamond = top_bottom(caret, caret_flip);

  render_fill(asciibuffer_2, diamond);
  render_ssim(asciibuffer, diamond, "");
  flatten(asciibuffer);

  //  for (int i = 0; i < height; ++i)
  //     printf("%.*s\n", width, asciibuffer_2->buffer + i*width);
  
  show_asciibuffer(asciibuffer);
  show_asciibuffer(asciibuffer_2);
  
  free(asciibuffer);
  free(asciibuffer_2);

  free(backslash.buffer);
  free(slash.buffer);
  
  free(diamond);
  free(caret_flip);
  free(caret);

  //  Printf("%f", ssim__unsigned_char(backslash_width*backslash_height,
  //				   0, 0,
  //				   backslash_width, backslash_width,
  //				   test_backslash(),
  //				   test_slash()));
  return 0;
}
