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
 *
 * @description:
 *   Bit manipulations library.
 *
 * @author:
 *   Roger Doss
 *
 */
#ifndef _BITS_H
#define _BITS_H
#include <stdio.h>

#define BIT_NR_BYTES(X) (((X) >> 3) + (((X) & 7) ? 1:0))

typedef struct bit {
    unsigned char *map;
    unsigned len;
} bit_t ;

typedef struct bit_range {
    unsigned start;
    unsigned   end;
} bit_range_t ;

/*
 * bit_make_range:
 *
 * Construct a range on the stack.  This is useful
 * in the call to bit_group.  For example, one may
 * have:
 *
 * bit_t *group = bit_group(map, 8, 2, bit_make_range(4,8),  // Source range.
 *                                     bit_make_range(0,4)); // Destination range.
 *
 */
bit_range_t bit_make_range( unsigned start, unsigned end );

/*
 * bit_init:
 *
 * Construct a bit map based on the user supplied number of bits.
 */
bit_t *bit_init(unsigned len);

/*
 * bit_init_val:
 *
 * Construct a bit map based on a 32 bit value.
 *
 */
bit_t *bit_init_val(unsigned val);

/*
 * bit_init_val64:
 *
 * Construct a bit map based on a 64 bit value.
 *
 */
bit_t *bit_init_val64(unsigned long long val);

/*
 * bit_init_val16:
 *
 * Construct a bit map based on a 16 bit value.
 *
 */
bit_t *bit_init_val16(unsigned short val);

/*
 * bit_init_val8:
 *
 * Construct a bit map based on a 8 bit value.
 *
 */
bit_t *bit_init_val8(unsigned short val);

/*
 * bit_copy_data:
 *
 * Construct a deep copy of 'src' bit map.
 */
bit_t *bit_copy_data( bit_t *src );

/*
 * bit_free:
 *
 * Free the bitmap.
 */
void bit_free(bit_t *map);

/*
 * bit_realloc:
 *
 * Reallocate the memory used by the bit map.
 */
bit_t *bit_realloc(bit_t *map, unsigned len);

/*
 * bit_get:
 *
 * Obtain a bit from the map at the specified position.
 * These are the most common functions of bit maps and
 * are optimized by being implemented as macros.
 *
 */
#define bit_get( MAP, BIT ) \
({ \
    register unsigned __rvalue = 0; \
    __rvalue = ((MAP)->map[((BIT)>> 3)] & (1 << ((BIT) & 7))); \
    __rvalue >>= ((BIT) & 7); \
    __rvalue; \
})

/*
 * bit_set:
 *
 * Set a bit in the map at the specified position.
 * These are the most common functions of bit maps and
 * are optimized by being implemented as macros.
 *
 */
#define bit_set( MAP, BIT, VALUE ) \
({ \
    register unsigned __rvalue = 0; \
    if(VALUE) { \
        __rvalue = (MAP)->map[((BIT) >> 3)] |= ((VALUE) << ((BIT) & 7)); \
    } else { \
        __rvalue = (MAP)->map[((BIT) >> 3)] &= ~((VALUE) << ((BIT) & 7)); \
    } \
    __rvalue; \
})

/*
 * bit_get_range:
 *
 * Given a map, and a desired range of either 0 or 1 bits,
 * and a length, return such a range in the map if one is found.
 *
 */
bit_range_t *
bit_get_range( bit_t *map, unsigned value, int run_len );

/*
 * bit_set_range:
 *
 * Given a map, set a range from a starting bit to an ending
 * bit to be a specified value.
 *
 */
void 
bit_set_range( bit_t *map, unsigned value, bit_range_t *range );

/*
 *
 * bit_copy:
 *
 * Deep copy a bitmap. 
 *
 */
void 
bit_copy( bit_t *dest, bit_range_t *dest_range, bit_t *src, bit_range_t *src_range );

/*
 * bit_group:
 *
 * This function takes an existing bit map and allows the caller
 * using variadic argument list, to specifiy a variable number
 * of arguments which are range pairs ( source and destination ).
 * For each range pair, the code copies the bits from one range
 * to another.  The size of the new bit map to be returned
 * is to supplied as an argument.  The caller must be
 * aware that the destination range can not exceed the
 * largest possible bit in the new bit map.
 *
 * An example use to copy bits 7 to 17 to bits 0 to 10:
 *
 * bit_t *group = bit_group(map, 10, 2, bit_make_range(7,17), bit_make_range(0,10));
 *
 * The function includes the length of the to be constructed 
 * bit map as part of the argument since it is also possible
 * ( and desirable ) for the caller to want to map the destination bis 
 * to range 2,12 for example.  If we were to try to deduce this from
 * the supplied ranges, it would be time consuming and potentially error prone.
 *
 */
bit_t *
bit_group( bit_t *map, unsigned group_bits, unsigned range_len, ... );

/*
 * bit_ror:
 *
 * Logical right rotation of bits.
 * Given a map such as:
 *
 * 0 1 2 3 4 5 6 7
 * 1 1 0 0 0 0 0 1 ( after performing a bit_ror )
 *
 * 1 1 1 0 0 0 0 0
 *
 * This function is the logical inverse
 * of bit_rol.
 *
 */
void
bit_ror( bit_t *map );

/*
 * bit_rol:
 *
 * Logical right rotation of bits.
 * Given a map such as:
 *
 * 0 1 2 3 4 5 6 7
 * 1 1 0 0 0 0 0 1 ( after performing a bit_rol )
 *
 * 1 0 0 0 0 0 1 1
 *
 * This function is the logical inverse
 * of bit_ror.
 *
 */
void
bit_rol( bit_t *map );

/*
 * bit_rshift:
 * bit_rshift_block:
 *
 * Shift the bits to the right by 1
 * or by len, respectively.
 *
 * The left most bit is set to zero.
 * Similar to C >> binary operator.
 *
 */
void
bit_rshift( bit_t *map );
void
bit_rshift_block( bit_t *map , unsigned len );

/*
 * bit_lshift:
 * bit_lshitf_block:
 *
 * Shift the bits to the left by 1 
 * or by len, respectively.
 * The right most bit is set to zero.
 * Similar to C << binary operator.
 *
 */
void
bit_lshift( bit_t *map );
void
bit_lshift_block( bit_t *map , unsigned len );

/*
 * bit_and:
 *
 * And the map bits for 'l' with 'r'.
 * Set the results in 'l'.
 */
void
bit_and( bit_t *l, bit_t *r );

/*
 * bit_or:
 *
 * Or the map bits for 'l' with 'r'.
 * Set the results in 'l'.
 */
void
bit_or( bit_t *l, bit_t *r );

/*
 * bit_not:
 *
 * Take the logical ! operation of
 * the map bits for 'l' with 'r'.
 * Set the results in 'l'.
 *
 */
void
bit_not( bit_t *map );

/*
 * bit_inv:
 *
 * Take the logical inverse of 
 * the map bits for 'l' with 'r'.
 * Set the results in 'l'.
 *
 */
void
bit_inv( bit_t *map );

/*
 * bit_xor:
 *
 * XOR the map bits for 'l' with 'r'.
 * Set the results in 'l'.
 *
 */
void
bit_xor( bit_t *l, bit_t *r );

/*
 * bit_nor:
 *
 * Or then take the logical inverse of 
 * the map bits for 'l' with 'r'.
 * Set the results in 'l'.
 *
 */
void
bit_nor( bit_t *l, bit_t *r );

/*
 * bit_nand:
 *
 * And then take the logical inverse 
 * of the map bits for 'l' with 'r'.
 * Set the results in 'l'.
 *
 */
void
bit_nand( bit_t *l , bit_t *r );

/*
 * bit_logical:
 *
 * Return 0 if all bits are 0, 1 otherwise.
 * This is used so the bit maps can be used in logical
 * operations.
 *
 */
unsigned
bit_logical( bit_t *map );

/*
 * bit_print_hex:
 * 
 * Stream out the bits in hex in the
 * following format:
 *
 *    hex{,hex}
 *
 * Useful for debugging.
 *
 */
void
bit_print_hex( FILE *out, bit_t *map );

/*
 * bit_print:
 *
 * Stream out the bits in binary 0 or 1
 * in the following format:
 *
 *   bin{,bin}
 *
 * Useful for debugging.
 *
 */
void
bit_print( FILE *out, bit_t *map );

/*
 * bit_in:
 *
 * Read in the binary data constructing a map
 * based upon it.
 *
 * Format is:
 * 
 * binary 4 byte              ( representing length )
 * binary unsigned char array ( representing bits   )
 *
 */
bit_t *
bit_in( FILE *in );

/*
 * bit_out:
 *
 * Write out the binary data.
 *
 * Format is:
 * 
 * binary 4 byte              ( representing length )
 * binary unsigned char array ( representing bits   )
 *
 */
void
bit_out( FILE *out, bit_t *map );

#endif /* _BITS_H */
