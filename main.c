#include<stdio.h>
#include"asciibufferfill.h"
#include"asciibufferssim.h"
#include"testimage.h"

#include "fonts/FixedsysExcelsior/backslash.xbm"

int main()
{
  printf("Hello World!\n");

  int width = backslash_width;
  int height = backslash_height;
  
  struct asciibuffer *asciibuffer = new_asciibuffer(width, height);

  // render_fill(asciibuffer, smiley_flat, 8, 8);
  render_ssim(asciibuffer, smiley_flat, 8, 8, "");
  flatten(asciibuffer);

  for (int i = 0; i < height; ++i)
    printf("%.*s\n", width, asciibuffer->buffer + i*width);
  return 0;
}
