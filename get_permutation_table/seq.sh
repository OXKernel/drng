#!/bin/bash
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
# @file:
#   get_rand
#
# @description:
#   Use the Perl client (random_org.pl) to obtain a set of random numbers from the
#   web and format them into a C table for compilation.
#
# @author:
#   Roger Doss
#
#############################################################

function get_rand()
{
    ./random_org.pl 0 31 |
      sed 's/^/{/g'  |
      sed 's/$/},/g' |
      sed 's/ /,/g'  |
      sed 's/{,/{/g' |
      sed 's/,}/}/g'
}

IDX=521 # Prime
I=0

while [ "$I" -lt "$IDX" ]
do
    printf "\n"
    get_rand
    ((I=$I + 1))
    sleep 2;
done
#
# EOF
#
