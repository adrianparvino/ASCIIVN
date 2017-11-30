#include<stdio.h>
#include<stdlib.h>
#include"asciibufferfill.h"
#include"asciibufferssim.h"
#include"xbmutils.h"
#include"imagemanip.h"
#include"testimage.h"

#include "fonts/FixedsysExcelsior/slash.xbm"
#include "fonts/FixedsysExcelsior/backslash.xbm"
#include "fonts/FixedsysExcelsior/pipe.xbm"

int main()
{
  int caretwidth = 16;
  int caretheight = 8;
  
  struct asciibuffer *asciibuffer = new_asciibuffer(caretwidth, caretheight);
  struct asciibuffer *asciibuffer2 = new_asciibuffer(caretwidth, caretheight);

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

  struct imagebuffer pipe =
    {
      .height = pipe_height,
      .width = pipe_width,
      .buffer = test_pipe()
    };

  struct imagebuffer hs =
    {
      .height = 8,
      .width = 8,
      .buffer = smiley_flat
    };
  
  struct imagebuffer *caret = side_by_side(&slash, &backslash);
  struct imagebuffer *caret_flip = side_by_side(&backslash, &slash);
  struct imagebuffer *diamond = top_bottom(caret, caret_flip);

  render_ssim(asciibuffer, &hs, "");
  render_fill(asciibuffer2, &hs, "");
  flatten(asciibuffer);

  show_asciibuffer(asciibuffer);
  show_asciibuffer(asciibuffer2);
  
  free(asciibuffer);
  free(asciibuffer2);

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
