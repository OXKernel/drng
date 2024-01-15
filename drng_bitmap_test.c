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
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "drng.h"
#include "bits/bits.h"

int
main()
{
  if(!al_init()) {
    fprintf(stderr,"main.c:: failed to initialize allegro 5!\n");
    return -1;
  }

  unsigned res    = 0;
	drng_t *rng     = drng_seed();
  al_init_image_addon();
  ALLEGRO_BITMAP *map = al_create_bitmap(1024,1024);

  al_set_target_bitmap(map);

  for (int i = 0; i < 1024; ++i) {
	  for (int j = 0; j < 1024; ++j) {
      res = drng_rand(rng);
      char bit = res % 2;
      al_put_pixel(i,j, al_map_rgb(0,0,0));
    }
  }

  for (int i = 0; i < 1024; ++i) {
	  for (int j = 0; j < 1024; ++j) {
      res = drng_rand(rng);
      char bit = res % 2;
      if(bit)  al_put_pixel(i,j, al_map_rgb(255,255,255));
      if(!bit) al_put_pixel(i,j, al_map_rgb(  0,  0,  0));
    }
  }

  if(al_save_bitmap("./drng_random.bmp", map)) {
    printf("sucessfully created bitmap\n");
  } else {
    fprintf(stderr, "failed to create bitmap\n");
  }
	drng_free(rng);
}
