#include<stdlib.h>
#include<aalib.h>
#include"asciibufferaa.h"

int render_aa(struct asciibuffer *dest,
              char *source,
              size_t width, size_t height)
{
  aa_context *context = aa_init(&mem_d, &aa_defparams, NULL);

  context->params.width = 16;
  context->params.height = 16;
  context->mulx = 8;
  context->muly = context->mulx;
  aa_resize(context);
  printf("Image: %dx%d\n"
         "Text: %dx%d\n",
         context->imgwidth, context->imgheight,
         context->params.width, context->params.height);

  aa_renderparams *params = aa_getrenderparams();
  
  aa_render(context, params, 0, 0, aa_scrwidth(context), aa_scrheight(context));
  //aa_fastrender(context, 0, 0, aa_scrwidth(context), aa_scrheight(context));
  aa_flush(context);

  
  printf("Image: %dx%d\n"
         "Text: %dx%d\n",
         context->imgwidth, context->imgheight,
         context->params.width, context->params.height);
  
  for(int i = 0; i < (context->params.width); ++i)
    printf("%.*s\n", (context->params.width), context->textbuffer + i*(context->params.width));
}
