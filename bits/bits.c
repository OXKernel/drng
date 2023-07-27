/***************************************************************************
 * Copyright (C) 2023. Roger Doss. All Rights Reserved.
 ***************************************************************************
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */
#include <stdarg.h>
#include <malloc.h>
#include <string.h>

#include "bits.h"

bit_range_t bit_make_range( unsigned start, unsigned end )
{
    bit_range_t range;
    range.start = start;
    range.end   = end;
    return range;

}/* bit_make_range */

bit_t *bit_init(unsigned len)
{
    register bit_t *map = (bit_t *)malloc(sizeof(bit_t));
    map->map = (unsigned char *)malloc(BIT_NR_BYTES(len));
    map->len = len; /* Number of bits. */
    return map;

}/* bit_init */

bit_t *bit_init_val(unsigned val)
{
    register bit_t *map = (bit_t *)malloc(sizeof(bit_t));
    map->map = (unsigned char *)malloc(4);
    memcpy((void *)map->map, (void *)&val, 4);
    map->len = 32;
    return map;

}/* bit_init_val */

bit_t *bit_init_val64(unsigned long long val)
{
    register bit_t *map = (bit_t *)malloc(sizeof(bit_t));
    map->map = (unsigned char *)malloc(8);
    memcpy((void *)map->map, (void *)&val, 8);
    map->len = 64;
    return map;

}/* bit_init_val64 */

bit_t *bit_init_val16(unsigned short val)
{
    register bit_t *map = (bit_t *)malloc(sizeof(bit_t));
    map->map = (unsigned char *)malloc(2);
    memcpy((void *)map->map, (void *)&val, 2);
    map->len = 16;
    return map;

}/* bit_init_val16 */

bit_t *bit_init_val8(unsigned short val)
{
    register bit_t *map = (bit_t *)malloc(sizeof(bit_t));
    map->map = (unsigned char *)malloc(1);
    memcpy((void *)map->map, (void *)&val, 1);
    map->len = 8;
    return map;

}/* bit_init_val8 */

bit_t *bit_copy_data( bit_t *src )
{
    bit_t *dest = bit_init(src->len);
    memcpy(dest->map, src->map, BIT_NR_BYTES(src->len));
    return dest;

}/* bit_copy_data */

void bit_free(bit_t *map)
{
    free((void *)map->map);
    free((void *)map);

}/* bit_free */

bit_t *bit_realloc(bit_t *map, unsigned len)
{
    bit_t *rtvl = bit_init(len);
    memcpy(rtvl->map, map->map, BIT_NR_BYTES(len));
    bit_free(map);
    return rtvl;

}/* bit_realloc */

bit_range_t *bit_get_range( bit_t *map, unsigned value, int run_len )
{
    register int i, bit, found = 0;
    bit_range_t *range = (bit_range_t *)malloc(sizeof(bit_range_t));

    for(i = 0; i < map->len; i++) {
            bit = bit_get(map, i);
            /* Scan for a range of 1 values. */
            if(value == 1) {
                if(bit == 1) {
                    if(!found) {
                        /* Mark the possible start of a range. */
                        range->start = i;
                    }
                    found++;
                    if(found == run_len) {
                        range->end = i;
                        goto SUCCESS;
                    }
                } else {
                    /* Reset the count. */
                    found = 0;
                }
            } else if(value == 0) {
                if(bit == 0) {
                    if(!found) {
                        /* Mark the possible start of a range. */
                        range->start = i;
                    }
                    found++;
                    if(found == run_len) {
                        range->end = i;
                        goto SUCCESS;
                    }
                } else {
                    /* Reset the count. */
                    found = 0;
                }
            }
    }

    free((void *)range);
    return NULL;

SUCCESS:
    return range;

}/* bit_get_range */

void bit_set_range( bit_t *map, unsigned value, bit_range_t *range )
{
    register int i;

    for(i = range->start; i <= range->end; i++) {
        bit_set(map, i, value);
    }

}/* bit_set_range */

void bit_copy( bit_t *dest, bit_range_t *dest_range, bit_t *src, bit_range_t *src_range )
{
    register int i, j, bit;

    for(j = dest_range->start, i = src_range->start; i <= src_range->end; i++, j++) {
        bit = bit_get(src, i);
        bit_set(dest, j, bit);
    }

}/* bit_copy */

bit_t *bit_group( bit_t *map, unsigned group_bits, unsigned range_len, ... )
{
    register int i, j, k;
    bit_t       *group;
    bit_range_t  src,  dest;
    va_list      args;
    unsigned     bit;

    va_start(args, range_len);
    {
        group = bit_init(group_bits);
        for(i = 0; i < range_len; i++) {
            src  = va_arg(args, bit_range_t);
            dest = va_arg(args, bit_range_t);
            for(j = dest.start, k = src.start; k <= src.end; j++, k++) {
                bit = bit_get(map, k);
                bit_set(group, j, bit);
            }
        }
    }
    va_end(args);
    return group;

}/* bit_group */

void
bit_ror( bit_t *map )
{
    register int i, s, r;
    register unsigned char *ptr;
    register bit_t *tmp = bit_init(map->len);

    bit_set(tmp, 0, bit_get(map, map->len - 1));
    for(i=0; i < map->len - 1; i++) {
        bit_set(tmp, i + 1, bit_get(map, i));
    }

    ptr = map->map;
    map->map = tmp->map;
    tmp->map = ptr;
    bit_free(tmp);

}/* bit_ror */

void
bit_rol( bit_t *map )
{
    register int i;
    register unsigned char  *ptr;
    register bit_t *tmp = bit_init(map->len);

    bit_set(tmp, map->len - 1, bit_get(map, 0));
    for(i = map->len - 1; i > 0; i--) {
    	bit_set(tmp, i - 1, bit_get(map, i));
    }

    ptr = map->map;
    map->map = tmp->map;
    tmp->map = ptr;
    bit_free(tmp);

}/* bit_rol */

void
bit_rshift( bit_t *map )
{
    register int i;
    register unsigned char *ptr;
    register bit_t *tmp = bit_init(map->len);

    bit_set(tmp, 0, 0);
    for(i=0; i < map->len - 1; i++) {
        bit_set(tmp, i + 1, bit_get(map, i));
    }

    ptr = map->map;
    map->map = tmp->map;
    tmp->map = ptr;
    bit_free(tmp);

}/* bit_rshift */

void
bit_lshift( bit_t *map )
{
    register int i;
    register unsigned char  *ptr;
    register bit_t *tmp = bit_init(map->len);

    bit_set(tmp, map->len - 1, 0);
    for(i = map->len - 1; i > 0; i--) {
    	bit_set(tmp, i - 1, bit_get(map, i));
    }

    ptr = map->map;
    map->map = tmp->map;
    tmp->map = ptr;
    bit_free(tmp);

}/* bit_lshift */

void
bit_rshift_block( bit_t *map , unsigned len )
{
    register int i, j;
    register unsigned char *ptr;
    register bit_t *tmp = bit_init(map->len);

    for( i = 0; i < len; i++) { 
        bit_set(tmp, i, 0);
    }

    for(i=0, j = len; i < map->len - 1 - len; j++, i++) {
        bit_set(tmp, j, bit_get(map, i));
    }

    ptr = map->map;
    map->map = tmp->map;
    tmp->map = ptr;
    bit_free(tmp);

}/* bit_rshift_block */

void
bit_lshift_block( bit_t *map , unsigned len )
{
    register int i, j;
    register unsigned char  *ptr;
    register bit_t *tmp = bit_init(map->len);

    for(i = map->len - 1, j = 0; j < len; i--, j++) {
        bit_set(tmp, i, 0);
    }

    for(i = len, j = 0; i < map->len; i++,j++) {
    	bit_set(tmp, j, bit_get(map, i));
    }

    ptr = map->map;
    map->map = tmp->map;
    tmp->map = ptr;
    bit_free(tmp);

}/* bit_lshift_block */

void
bit_and( bit_t *l, bit_t *r )
{
    register int i = 0;
    for(; i < BIT_NR_BYTES(l->len); i++) {
        l->map[i] &= r->map[i];
    }

}/* bit_and */

void
bit_or( bit_t *l, bit_t *r )
{
    register int i = 0;
    for(; i < BIT_NR_BYTES(l->len); i++) {
        l->map[i] |= r->map[i];
    }

}/* bit_or */

void
bit_not( bit_t *map )
{
    register int i = 0;
    for(; i < BIT_NR_BYTES(map->len); i++) {
        map->map[i] = !map->map[i];
    }

}/* bit_not */

void
bit_inv( bit_t *map )
{
    register int i = 0;
    for(; i < BIT_NR_BYTES(map->len); i++) {
        map->map[i] = ~map->map[i];
    }

}/* bit_inv */

void
bit_xor( bit_t *l, bit_t *r )
{
    register int i = 0;
    for(; i < BIT_NR_BYTES(l->len); i++) {
        l->map[i] ^= r->map[i];
    }

}/* bit_xor */

void
bit_nor( bit_t *l, bit_t *r )
{
    register int i = 0;
    for(; i < BIT_NR_BYTES(l->len); i++) {
        l->map[i] |= r->map[i];
        l->map[i] = ~l->map[i];
    }

}/* bit_nor */

void
bit_nand( bit_t *l , bit_t *r )
{
    register int i = 0;
    for(; i < BIT_NR_BYTES(l->len); i++) {
        l->map[i] &= r->map[i];
        l->map[i] = ~l->map[i];
    }

}/* bit_nand */

unsigned
bit_logical( bit_t *map )
{
    register int i = 0;

    for(; i < map->len; i++) {
        if(bit_get(map, i)) {
            return 1;
        }
    }
    return 0;

}/* bit_logical */

void
bit_print_hex( FILE *out, bit_t *map )
{
    register unsigned i = 0;

    for( ; i < BIT_NR_BYTES(map->len); i++) {
        fprintf(out, "%x,", map->map[i]);
    }

}/* bit_print_hex */

void
bit_print( FILE *out, bit_t *map )
{
    register unsigned i = 0;

    for( ; i < map->len; i++) {
        fprintf(out, "%u,", bit_get(map,i));
    }

}/* bit_print_hex */

bit_t *
bit_in( FILE *in )
{
    unsigned len;
    bit_t *map;
    fread((void *)&len, 4, 1, in);
    map = bit_init(len);
    fread(map->map, BIT_NR_BYTES(map->len), 1, in);
    return map;

}/* bit_in */

void
bit_out(FILE *out, bit_t *map)
{
    fwrite((void *)&map->len, 4, 1, out);
    fwrite(map->map, BIT_NR_BYTES(map->len), 1, out);

}/* bit_out */
/*
 * EOF
 */
