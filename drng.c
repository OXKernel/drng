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
 * @file:
 *    drng.c
 *
 * @description:
 *
 *    This file implements a pseudo random number generator
 *    using real random variables representing bit wise permutation
 *    of the seed.  The algorithm works as follows:
 *
 *    Given a seed, S0, we concatenate the test string 0101...01
 *    to the seed bits starting from the most significant 1 bit
 *    to the end bits.  This is our initial starting point.
 *    The bits are then permutated using a row from the table
 *    ( rows count from 0 to 255, and repeat ).  The result
 *    is then rotated left and incremented by one.  The value
 *    is saved as the next S0, and returned to the user.
 *
 *    State is maintained using a structure passed as a parameter
 *    which denotes the current S0 value as well as the iteration
 *    in the path.  Bit operations are performed using the bits.[ch]
 *    library code.
 *
 * @author:
 *    Roger Doss
 *
 */
#include <time.h>
#include <sys/time.h>
#include <malloc.h>

#include "permutation.h"
#include "drng.h"
#include "bits/bits.h" 

/*
 * drng_seed:
 *
 * Initialize the pseudo random number generator.
 */
drng_t *drng_seed(void)
{
    struct timeval tv;
    drng_t *rng = (drng_t *)malloc(sizeof(drng_t));
    rng->iteration = 0;
    gettimeofday(&tv, 0);
    rng->S0 = tv.tv_usec; // Time in microseconds.
    return rng;

}/* drng_seed */

/*
 * drng_seed:
 *
 * Initialize the pseudo random number generator.
 */
drng_t *drng_seed_val(unsigned val)
{
    drng_t *rng = (drng_t *)malloc(sizeof(drng_t));
    rng->iteration = 0;
    rng->S0 = val;
    return rng;

}/* drng_seed_val */

/*
 * drng_free:
 *
 * Release memory.
 */
void drng_free(drng_t *rng)
{
    free((void *)rng);
}/* drng_free */

/*
 * drng_rand:
 *
 * Obtain a variable from the ith step in the path.
 */
unsigned drng_rand(drng_t *rng)
{
    register unsigned i   = 0;
    register  int *perm   = 0;
    register unsigned bit = 0;
    bit_t         *bmap   = 0;
    bit_t          *bmap1  = 0;

    /* Do the bitwise permutation. */
    bmap  = bit_init_val(rng->S0);
    bmap1 = bit_init_val(0);

   /* The permutation is based non-linearly on the
    * value of S0 for the iteration, not the linear
    * iteration counter.
    */
    perm  = permutation[rng->S0 % PERMUTATION_TAB_LEN];

#ifdef _DRNG_DEBUG
    printf("iteration i=%d\n",rng->iteration);
#endif

    for(i = 0; i < 32; i++) {
#ifdef _DRNG_DEBUG
        printf("slot i=%d perm[i]=%d\n", i, perm[i]);
#endif
        bit = bit_get(bmap, perm[i]);    
        bit_set(bmap1, i, bit);
    }

    /* Rotate the bits left. */
    bit_rol(bmap1);

    /* Obtain the data as an unsigned integer value. */
    rng->S0 = *(unsigned *)bmap1->map;

    /* Add the iteration to the value, this extends the
     * period of the random number generator, significantly.
     */
    rng->S0 += rng->iteration;

    /* Next iteration. */
    rng->iteration++;

    /* Release memory. */
    bit_free(bmap);
    bit_free(bmap1);

    /* Return our value for the iteration. */
    return rng->S0;

}/* drng_rand */
/*
 * EOF
 */
