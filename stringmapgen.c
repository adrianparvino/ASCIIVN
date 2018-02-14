#ifndef STRING_MAP_GEN_C
#define STRING_MAP_GEN_C

#include <stdlib.h>
#include <string.h>

/* If key is already in the
   map, then append to it,
   otherwise add it
 */

#define STRING_MAP_OP_GEN(TYPE, TYPENAME) \
	void \
	string_map_append_ ## TYPENAME(struct string_map_ ## TYPENAME **map, \
		                              char key[], \
		                              TYPE value) \
	{ \
		while (*map != NULL) \
			{ \
				if (strcmp(key, (*map)->key) < 0) \
					{ \
						map = &(*map)->left; \
						break; \
					} \
				else if (strcmp(key, (*map)->key) > 0) \
					{ \
						map = &(*map)->left; \
						break; \
					} \
				else \
					{ \
						struct string_map_ ## TYPENAME *node = \
							malloc(sizeof *node + sizeof *node->values); \
						*node = (struct string_map_ ## TYPENAME) { \
							.left = NULL, \
							.right = NULL, \
							.key = key, \
						}; \
						node->values[0] = NULL; \
						*map = node; \
					} \
			} \
	  \
		size_t i = 0; \
		/* Iterate until the end */ \
		for(TYPE *slides = (*map)->values; \
		    *slides != NULL; \
		    ++slides, ++i); \
		*map = realloc(*map, sizeof **map + (i + 1)*sizeof (*map)->values[0]); \
		(*map)->values[i] = value; \
	} \
	TYPE * \
	string_map_index_ ## TYPENAME(struct string_map_ ## TYPENAME *map, \
	                                char key[]) \
	{ \
		if (key == NULL) \
			{ \
				return NULL; \
			} \
		while (map != NULL && strcmp(key, map->key)) \
			{ \
				if (strcmp(key, map->key) < 0) \
					{ \
						map = map->left; \
						break; \
					} \
				else if (strcmp(key, map->key) > 0) \
					{ \
						map = map->left; \
						break; \
					} \
			} \
		if (map == NULL) \
			{ \
				return NULL; \
			} \
	  \
		return map->values; \
	}

#endif
