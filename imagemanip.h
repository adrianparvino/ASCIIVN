/* This file is part of ASCIIVN.
 *
 * Copyright (C) 2017  Adrian Parvin D. Ouano
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef IMAGEMANIP_H
#define IMAGEMANIP_H

#include <png.h>
#include "imagebuffer.h"
int color_type_to_bytes(int color_type);

struct imagebuffer *side_by_side(struct imagebuffer *x,
                                 struct imagebuffer *y);
struct imagebuffer *top_bottom(struct imagebuffer *x,
                               struct imagebuffer *y);
struct imagebuffer *extract(size_t column_offset,
                            size_t row_offset,
                            size_t width,
                            size_t height,
                            struct imagebuffer *x);

void scale_nearest(struct imagebuffer *dest,
                   struct imagebuffer *src);

void scale_bilinear(struct imagebuffer *dest,
                    struct imagebuffer *src);

#endif
