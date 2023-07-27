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
#include "byte.h"

#define htonll(x) (((unsigned long long)(ntohl((int)((x << 32) >> 32))) << 32) | (unsigned int)ntohl(((int)(x >> 32))))

int
main()
{
	{
	unsigned int val  = 0x07C0;
	unsigned int val1 = htonl(val);
	unsigned int val2 = 0x07C0;
	printf("testing int conversion\n");
	byte_order_t border = byte_order();
	if(border == BYTE_BIG_ENDIAN) {
		printf ("BIG ENDIAN\n");
	} else if(border == BYTE_LITTLE_ENDIAN) {
		printf ("LITTLE ENDIAN\n");
	}
	byte_swap(&val);
	if(val1 == val) {
		printf ("BIG ENDIAN\n");
	} else if(val2 == val) {
		printf ("LITTLE ENDIAN\n");
	}
	byte_swap(&val);
	if(val1 == val) {
		printf ("BIG ENDIAN\n");
	} else if(val2 == val) {
		printf ("LITTLE ENDIAN\n");
	}
	}
	{
	// Expect little, big, little.
	unsigned short val  = 0x07C0;
	unsigned short val1 = htons(val);
	unsigned short val2 = 0x07C0;
	printf("testing short conversion\n");
	byte_order_t border = byte_order();
	if(border == BYTE_BIG_ENDIAN) {
		printf ("BIG ENDIAN\n");
	} else if(border == BYTE_LITTLE_ENDIAN) {
		printf ("LITTLE ENDIAN\n");
	}
	byte_swap_16(&val);
	if(val1 == val) {
		printf ("BIG ENDIAN\n");
	} else if(val2 == val) {
		printf ("LITTLE ENDIAN\n");
	}
	byte_swap_16(&val);
	if(val1 == val) {
		printf ("BIG ENDIAN\n");
	} else if(val2 == val) {
		printf ("LITTLE ENDIAN\n");
	}
	}
	{
	// This code is assumed to be correct,
	// however, an alternative to the general
	// approach has not been found.
	// Though, swab seems to work, less the
	// sign on the zero.
	// Expect little, big, little.
	double val  = -2328323920000;
	unsigned long long tmp = -2328323920000;
	double val1 = htonll(tmp);
	double val2 = -2328323920000;
	unsigned long long tmp1 = (unsigned long long)val1;
	double val3 = htonll(tmp1);
	swab(&val,&val3,8);
	printf("here %f\n",val3);
	swab(&val3,&val, 8);
	printf("here %f\n",val);
	printf("testing generic conversion\n");
	byte_order_t border = byte_order();
	if(border == BYTE_BIG_ENDIAN) {
		printf ("BIG ENDIAN\n");
	} else if(border == BYTE_LITTLE_ENDIAN) {
		printf ("LITTLE ENDIAN\n");
	}
	byte_swap_s((unsigned char *)&val,8);
	if(val1 == val) {
		printf ("BIG ENDIAN\n");
	} else if(val2 == val) {
		printf ("LITTLE ENDIAN\n");
	}
	byte_swap_s((unsigned char *)&val,8);
	if(val1 == val) {
		printf ("BIG ENDIAN\n");
	} else if(val2 == val) {
		printf ("LITTLE ENDIAN\n");
	}
	}
	{
	// Expect little, big, little.
	unsigned long long val  = 0x07C0;
	unsigned long long val1 = htonll(val);
	unsigned long long val2 = 0x07C0;
	printf("testing long long conversion\n");
	byte_order_t border = byte_order();
	if(border == BYTE_BIG_ENDIAN) {
		printf ("BIG ENDIAN\n");
	} else if(border == BYTE_LITTLE_ENDIAN) {
		printf ("LITTLE ENDIAN\n");
	}
	byte_swap_64(&val);
	if(val1 == val) {
		printf ("BIG ENDIAN\n");
	} else if(val2 == val) {
		printf ("LITTLE ENDIAN\n");
	}
	byte_swap_64(&val);
	if(val1 == val) {
		printf ("BIG ENDIAN\n");
	} else if(val2 == val) {
		printf ("LITTLE ENDIAN\n");
	}
	}
	// Expect little, big, little.
}// main
