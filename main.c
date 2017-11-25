#include<stdio.h>
#include"asciibufferfill.h"
#include"testimage.h"

int main()
{
  printf("Hello World!\n");

  int width = 32;
  int height = 16;
  struct asciibuffer *asciibuffer = new_asciibuffer(width, height);

  render_fill(asciibuffer, smiley_flat, 8, 8);
  flatten(asciibuffer);

  for (int i = 0; i < height; ++i)
    printf("%.*s\n", width, asciibuffer->buffer + i*width);
  return 0;
}
