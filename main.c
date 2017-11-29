#include<stdio.h>
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

  int width = backslash_width*2;
  int height = backslash_height/2;
  
  struct asciibuffer *asciibuffer = new_asciibuffer(width, height);
  struct asciibuffer *asciibuffer_2 = new_asciibuffer(width, height);

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

  struct imagebuffer *caret = side_by_side(&slash, &backslash);

  // unsigned char *backslash = xbm_to_char_arr(backslash_bits, backslash_width, backslash_height);
  render_fill(asciibuffer_2, caret);
  render_ssim(asciibuffer, caret, "");
  flatten(asciibuffer);

  for (int i = 0; i < height; ++i)
     printf("%.*s\n", width, asciibuffer_2->buffer + i*width);
  
  for (int i = 0; i < height; ++i)
    printf("%.*s\n", width, asciibuffer->buffer + i*width);

  free(asciibuffer);
  free(asciibuffer_2);

  free(backslash.buffer);
  free(slash.buffer);
  free(caret);

  //  Printf("%f", ssim__unsigned_char(backslash_width*backslash_height,
  //				   0, 0,
  //				   backslash_width, backslash_width,
  //				   test_backslash(),
  //				   test_slash()));
  return 0;
}
