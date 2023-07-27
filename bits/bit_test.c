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
#include "bits.h"

int
main()
{
	/* All functions need to be tested. bit_rol is wrong. */
	int i = 0;
    /* Test the core bit map functionality. */
	bit_t *bmap = bit_init(32);
	bit_set(bmap, 0,  1);
    bit_set(bmap, 1,  1);
    bit_set(bmap, 30, 1);
	bit_set(bmap, 31, 0);
    bit_print(stdout,bmap);
    printf("\n");

    printf("bit_rol\n");
	bit_rol(bmap);
    bit_print(stdout,bmap);
	printf("\n");

    printf("bit_ror\n");
    bit_ror(bmap);
    bit_print(stdout,bmap);
	printf("\n");

    printf("bit_ror\n");
    bit_ror(bmap);
    bit_print(stdout,bmap);
	printf("\n");

    printf("bit_rol\n");
    bit_rol(bmap);
    bit_print(stdout,bmap);
	printf("\n");

    printf("bit_ror\n");
    bit_ror(bmap);
    bit_print(stdout,bmap);
	printf("\n");

    printf("bit_ror\n");
    bit_ror(bmap);
    bit_print(stdout,bmap);
	printf("\n");

    printf("bit_ror\n");
    bit_ror(bmap);
    bit_print(stdout,bmap);
	printf("\n");

    printf("bit_rol\n");
    bit_rol(bmap);
    bit_print(stdout,bmap);
	printf("\n");

    printf("bit_rol\n");
    bit_rol(bmap);
    bit_print(stdout,bmap);
    printf("\n");

    printf("bit_rol\n");
    bit_rol(bmap);
    bit_print(stdout,bmap);
    printf("\n");

    printf("bit_rshift\n");
    bit_rshift(bmap);
    bit_print(stdout,bmap);
	printf("\n");

    printf("bit_rshift\n");
    bit_rshift(bmap);
    bit_print(stdout,bmap);
	printf("\n");

    printf("bit_lshift\n");
    bit_lshift(bmap);
    bit_print(stdout,bmap);
	printf("\n");

    printf("bit_lshift\n");
    bit_lshift(bmap);
    bit_print(stdout,bmap);
	printf("\n");

    bit_set(bmap, 4, 1);
    bit_set(bmap, 5, 1);
    bit_set(bmap, 6, 1);
    bit_set(bmap, 7, 1);

    bit_range_t *range = bit_get_range(bmap, 1, 4);
    printf("start = %d end = %d\n", range->start, range->end);

    printf("shift block\n");
    bit_print(stdout,bmap);
    printf("\n");
    bit_rshift_block(bmap, 4);
    bit_print(stdout,bmap);
    printf("\n");

	bit_free(bmap);

}/* main */
/*
 * EOF
 */
