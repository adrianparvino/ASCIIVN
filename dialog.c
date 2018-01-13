#include "dialog.h"

void
render_dialogs(struct asciibuffer *asciibuffer)
               struct dialog *dialogs,
               size_t dialogs_count,
               int option)
{
	size_t offsetx = 2;
	size_t offsety = 2;

	size_t paddingx = 2;
	size_t paddingy = 2;

	size_t y = asciibuffer->height - 2*offsety - 2*paddingy;

	for (size_t x = offsetx;
	     x < asciibuffer->width - 2;
	     ++x)
		{
			printf("+");
		}
	printf("\n");
	i < asciibuffer->height - offsety;
	++i;
	     
}
