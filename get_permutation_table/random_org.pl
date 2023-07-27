#!/usr/bin/perl
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
use strict;
use warnings;
use LWP::Simple;

my $url = "https://www.random.org/integers/?num=32&min=$ARGV[0]&max=$ARGV[1]&col=1&base=10&format=plain&rnd=new";
my $content = get $url;
die "Couldn't get $url" unless defined $content;

chomp($content);

$content =~ s/\n/ /g; # Output single line with all 32 values on it.
print $content . "\n";
