#ifndef _DRNG_H
#define _DRNG_H
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
 *
 * @file:
 *    drng.h
 *
 * @description:
 *
 *    This file implements a pseudo random number generator.
 *
 * @author:
 *    Roger Doss
 *
 */

typedef struct drng {
    unsigned iteration; /* i'th step in the path.          */
    unsigned S0;        /* Seed value from the i-1 step. */
} drng_t;

/*
 * drng_seed:
 *
 * Initialize the pseudo random number generator.
 */
drng_t *drng_seed(void);

/*
 * drng_seed:
 *
 * Initialize the pseudo random number generator.
 */
drng_t *drng_seed_val(unsigned val);

/*
 * drng_free:
 *
 * Release memory.
 */
void drng_free(drng_t *rng);

/*
 * drng_rand:
 *
 * Obtain a variable from the ith step in the path.
 */
unsigned drng_rand(drng_t *rng);

#endif /* _DRNG_H */
