/*
  sse2.h: Copyright (C) 2012-2013  Oka Motofumi

  Author: Oka Motofumi (chikuzen.mo at gmail dot com)

  This file is part of GenericFilters.

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with the author; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/


#ifndef SSE2_DEFINE_HEADER
#define SSE2_DEFINE_HEADER

#include <string.h>
#include <stdint.h>
#include <emmintrin.h>

#ifdef _MSC_VER
#define GF_ALIGN __declspec(align(16))
#define GF_FUNC_ALIGN
#else
#define GF_ALIGN __attribute__((aligned(16)))
#define GF_FUNC_ALIGN __attribute__((force_align_arg_pointer))
#endif


static inline void VS_CC
line_copy8(uint8_t *line, const uint8_t *srcp, int width, int mergin)
{
    int w = ((width + 15) / 16) * 16;
    memcpy(line, srcp, w);
    for (int i = mergin; i > 0; i--) {
        *(line - i) = *line;
        *(line + width - 1 + i) = *(line + width - 1);
    }
}


static inline void VS_CC
line_copy16(uint16_t *line, const uint16_t *srcp, int width, int mergin)
{
    int w = ((width * 2 + 15) / 16) * 16;
    memcpy(line, srcp, w);
    for (int i = mergin; i > 0; i--) {
        line[0 - i] = line[0];
        line[width + i - 1] = line[width - 1];
    }
}

#endif