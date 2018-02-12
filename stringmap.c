#include "stringmap.h"
#include <stdlib.h>
#include <string.h>

/* If key is already in the
   map, then append to it,
   otherwise add it
 */
void
string_map_append(struct string_map **map,
                  char key[],
                  struct slide **value)
{
	while (*map != NULL)
		{
			if (strcmp(key, (*map)->key) < 0)
				{
					map = &(*map)->left;
					break;
				}
			else if (strcmp(key, (*map)->key) > 0)
				{
					map = &(*map)->left;
					break;
				}
			else
				{
					struct string_map *node = malloc(sizeof *node + sizeof *node->slides);
					*node = (struct string_map) {
						.left = NULL,
						.right = NULL,
						.key = key,
					};
					node->slides[0] = NULL;
					*map = node;
				}
		}

	size_t i = 0;
	// Iterate until the end
	for(struct slide ***slides = (*map)->slides;
	    *slides != NULL;
	    ++slides, ++i);
	*map = realloc(*map, sizeof **map + (i + 1)*sizeof (*map)->slides[0]);
	(*map)->slides[i] = value;
}

struct slide ***
string_map_index(struct string_map *map,
                 char key[])
{
	while (map != NULL && strcmp(key, map->key))
		{
			if (strcmp(key, map->key) < 0)
				{
					map = map->left;
					break;
				}
			else if (strcmp(key, map->key) > 0)
				{
					map = map->left;
					break;
				}
		}
	if (map == NULL)
		{
			return NULL;
		}
	
	return map->slides;
}
