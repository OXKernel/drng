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
 ***************************************************************************/
#include <stdio.h>
#include "drng.h"
#include "bits/bits.h"

int
main()
{
    unsigned int i  = 0;
    unsigned res    = 0;
    drng_t *rng     = drng_seed();
    bit_t  *map     = 0;

#ifdef _PRINT_SEED
    printf("Seed=%d\n", rng->S0);
#endif
    for ( ; i < (1 << 8); i++ ) {
#ifdef _INT
        printf("%u\n", drng_rand(rng));    
#elif _HEX
        printf("%x\n", drng_rand(rng));
#elif _BINARY
        res = drng_rand(rng);
        fwrite(&res, 4, 1, stdout);
#elif _ASCII
        drng_rand(rng);
        map = bit_init_val(rng->S0);
        bit_print(stdout,map);
        printf("\n");
        bit_free(map);
#endif
  }

  drng_free(rng);
}
