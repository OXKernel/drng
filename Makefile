#############################################################
# Copyright (C) 2023. Roger Doss. All Rights Reserved.
#############################################################
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
# 
#
CFLAGS=-D_INT -g
OBJS=drng.o drng_test.o drng_bitmap_test.o

ALL: $(OBJS)
	gcc drng.o drng_test.o -o drng_test -L./bits -lbits
	gcc drng.o drng_bitmap_test.o -o drng_bitmap_test -L./bits -lbits -lallegro -lallegro_image

LIB: $(OBJS)
	ar rv libdrng.a drng.o

clean:
	rm -f *.o core drng_test drng_bitmap_test
