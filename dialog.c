#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "dialog.h"

size_t
render_dialogs(struct asciibuffer *asciibuffer,
               char *message,
               struct dialog *dialogs[],
               size_t dialogs_count,
               size_t option)
{
	clear(asciibuffer);
		
	size_t offsetx = 2;
	size_t offsety = 2;

	size_t paddingx = 2;
	size_t paddingy = 2;
	size_t paddingchoice = 2;
	size_t paddingmessage = 2;

	size_t y = offsety;
	size_t x = offsetx;

	// Add top border
	for (x = offsetx;
	     x < asciibuffer->width - offsetx;
	     ++x)
		{
			*index_gray((struct imagebuffer *) asciibuffer, x, y) = '+';
		}
	++y;
	
	for (size_t i = 1;
	     i < paddingy;
	     ++i, ++y)
		{
			// Add left border
			x = offsetx;
			*index_gray((struct imagebuffer *) asciibuffer, x, y) = '+';
			
			//Add right border
			x = asciibuffer->width - offsetx - 1;
			*index_gray((struct imagebuffer *) asciibuffer, x, y) = '+';
		}

	// Add message
	// Add left border
	x = offsetx;
	*index_gray((struct imagebuffer *) asciibuffer, x, y) = '+';

	// Add text
	size_t j;
	for (j = 0, x += paddingx + paddingchoice;
	     message[j] != '\0' &&
		     x < asciibuffer->width - offsetx - paddingx + paddingchoice;
	     ++x, ++j)
		{
			*index_gray((struct imagebuffer *) asciibuffer, x, y) = message[j];
		}

	//Add right border
	x = asciibuffer->width - offsetx - 1;
	*index_gray((struct imagebuffer *) asciibuffer, x, y) = '+';
	++y;

	// Add message-response padding
	for (size_t i = 1;
	     i < paddingmessage;
	     ++i, ++y)
		{
			// Add left border
			x = offsetx;
			*index_gray((struct imagebuffer *) asciibuffer, x, y) = '+';
			
			//Add right border
			x = asciibuffer->width - offsetx - 1;
			*index_gray((struct imagebuffer *) asciibuffer, x, y) = '+';
		}

	// Add responses
	for (size_t i = 0;
	     i < dialogs_count;
	     ++i, ++y)
		{
			// Add left border
			x = offsetx;
			*index_gray((struct imagebuffer *) asciibuffer, x, y) = '+';

			// Add text
			size_t j;
			for (j = 0, x += paddingx + paddingchoice;
			     dialogs[i]->message[j] != '\0' &&
				     x < asciibuffer->width - offsetx - paddingx + paddingchoice;
			     ++x, ++j)
				{
					*index_gray((struct imagebuffer *) asciibuffer, x, y) = dialogs[i]->message[j];
				}

			//Add right border
			x = asciibuffer->width - offsetx - 1;
			*index_gray((struct imagebuffer *) asciibuffer, x, y) = '+';
		}

	// Add bottom border
	for (size_t i = 1;
	     i < paddingy;
	     ++i, ++y)
		{
			// Add left border
			x = offsetx;
			*index_gray((struct imagebuffer *) asciibuffer, x, y) = '+';
			
			//Add right border
			x = asciibuffer->width - offsetx - 1;
			*index_gray((struct imagebuffer *) asciibuffer, x, y) = '+';
		}
	
	for (x = offsetx;
	     x < asciibuffer->width - offsetx;
	     ++x)
		{
			*index_gray((struct imagebuffer *) asciibuffer, x, y) = '+';
		}
	
	y += offsety;

	flatten(asciibuffer);
	
	asciibuffer->height = y;

	return y;
}

struct dialog *
make_dialog(struct slide *next,
            char *message)
{
	int n = strlen(message);

	struct dialog *dialog = malloc(sizeof *dialog + n + 1);
	*dialog = (struct dialog) {
		.next = next,
		.message = dialog->in_message
	};
	strcpy(dialog->in_message, message);

	return dialog;
}
