#include "stringmap.h"
#include "stringmapgen.c"
#include <stdlib.h>
#include <string.h>

/* STRING_MAP_OP_GEN(struct slide **, slide_next_ptr) */
void
string_map_append_slide_next_ptr(struct string_map_slide_next_ptr **map,
                                 char key[],
                                 struct slide ** value)
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
					size_t i = 0;
					/* Iterate until the end */
					for(struct slide ***slides = (*map)->values;
					    *slides != NULL;
					    ++slides, ++i);
					*map = realloc(*map, sizeof **map + (i + 2)*sizeof (*map)->values[0]);
					(*map)->values[i] = value;
					(*map)->values[i+1] = NULL;
					
					return;
				}
		}
	struct string_map_slide_next_ptr *node =
		malloc(sizeof *node + 2*sizeof *node->values);
	*node = (struct string_map_slide_next_ptr) {
		.left = NULL,
		.right = NULL,
		.key = key,
	};
	node->values[0] = value;
	node->values[1] = NULL;
	*map = node;
}

struct slide ***
string_map_index_slide_next_ptr(struct string_map_slide_next_ptr *map,
                                char key[])
{
	if (key == NULL)
		{
			return NULL;
		}
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
	 
	return map->values;
}
