#include <string.h>
#include <math.h>
#include <stdio.h>

#include "asciibufferfill.h"
#include "imagemanip.h"
#include "charset.h"

void render_fill(struct asciibuffer *dest,
                struct imagebuffer *src,
                char fontname[])
{
  struct charset *font_charset = NULL;
  
  if (!strcmp(fontname, ""))
    {
      fprintf(stderr, "Warning: no fontname provided. Using fallback.\n");
      
      font_charset = generate_test_charset();
    }
  
  scale_bilinear((struct imagebuffer *)dest, src);

  float cache_value[font_charset->n];
  char cache_character[font_charset->n];

  memset(cache_value, 0, sizeof(*cache_value)*font_charset->n);
  memset(cache_character, 0, font_charset->n);

  // TODO: Use a sorted array
  for (size_t character = 0; character < font_charset->n; ++character)
    {
      for (size_t i = 0; i < font_charset->width * font_charset->height; ++i)
        {
          float dx = font_charset->characters[character].glyph[i] - cache_value[character];
          cache_value[character] += dx/(i + 1);
        }
      
      cache_character[character] = font_charset->characters[character].character;
    }
  
  for (size_t i = 0; i < dest->height * dest->width; ++i)
    {
      float best_value = 1.0/0;
      char best_character = 0;
      
      for (size_t j = 0; j < font_charset->n; ++j)
        {
          float current_value = fabs(((unsigned char*)(dest->buffer))[i] - cache_value[j]);
          if (current_value < best_value)
            {
              best_value = current_value;
              best_character = cache_character[j];
            }
        }
      
      dest->buffer[i] = best_character;
    }

  free_charset(font_charset);
}
