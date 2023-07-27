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
#ifndef _BYTE_H
#define _BYTE_H
#include <netinet/in.h>

typedef enum {
    BYTE_LITTLE_ENDIAN,
    BYTE_BIG_ENDIAN
} byte_order_t ;

/*
 * byte_order:
 *
 * Return whether or not the data is little
 * or big endian.
 *
 */
inline
byte_order_t byte_order(void)
{
    int value = 0x0001;
    if(value == htonl(value)) {
        return BYTE_BIG_ENDIAN;
    } else {
        return BYTE_LITTLE_ENDIAN;
    }

}/* byte_order */

/*
 * byte_swap:
 *
 * Convert the input by swaping the bytes.
 * If the call is done on a little endian data,
 * it will become big endian, and vice versa.
 * NOTE: The pointer is interpreted as a single
 *       element who's address has been supplied
 *       with the intention that the function
 *       will change its value.  It is not
 *       being interpreted as an array.
 *
 */
#define BYTE_SWAP(X) byte_swap((unsigned int)&(X))

inline
unsigned int byte_swap( unsigned int *value )
{
	unsigned int value1 = 0;
	register unsigned char *tmp = (unsigned char *)&value1;
	register unsigned char *ptr = (unsigned char *)value;

	tmp[0] = ptr[3];
	tmp[1] = ptr[2];
	tmp[2] = ptr[1];
	tmp[3] = ptr[0];

	*value = value1;
	return value1;

}/* byte_swap */

/*
 * byte_swap_16:
 */
#define BYTE_SWAP_16(X) byte_swap_16((unsigned short *)&(X))
inline
unsigned short byte_swap_16(unsigned short *value)
{
	unsigned short value1 = 0;
	register unsigned char *tmp = (unsigned char *)&value1;
	register unsigned char *ptr = (unsigned char *)value;

	tmp[0] = ptr[1];
	tmp[1] = ptr[0];

	*value = value1;
	return value1;

}/* byte_swap_16 */

/*
 * byte_swap_64:
 */
#define BYTE_SWAP_64(X) byte_swap_16((unsigned long long *)&(X))
inline
unsigned int byte_swap_64( unsigned long long *value )
{
	unsigned long long value1 = 0;
	register unsigned char *tmp = (unsigned char *)&value1;
	register unsigned char *ptr = (unsigned char *)value;

	tmp[0] = ptr[7];
	tmp[1] = ptr[6];
	tmp[2] = ptr[5];
	tmp[3] = ptr[4];
	tmp[4] = ptr[3];
 	tmp[5] = ptr[2];
	tmp[6] = ptr[1];
	tmp[7] = ptr[0];
        
	*value = value1;
	return value1;

}/* byte_swap */

/*
 * byte_swap_s:
 *
 * Convert any type from one form to another.
 */
#define BYTE_SWAP_S(X) byte_swap_s((unsigned char *)&(X), sizeof((X)))

inline
unsigned char *byte_swap_s(unsigned char *str, int len)
{
	register int i = 0, j = len-1;
	register unsigned char tmp;

	while(i<j) {
		// Swap.
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++; j--;
	}
	return str;

}/* byte_swap_s */

#endif /* _BYTE_H */
