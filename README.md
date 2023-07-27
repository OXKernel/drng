# drng
Pseudo Random Number Generator

# Approach

* Obtains a real random number stream from random.org using
  get\_permutation\_table code (run seq.sh). This generates
  a table with 521 (prime) rows. This is user configurable.

* bit manipulation library is provided in bits directory, and
  must be compiled after generating the permutation table.

* drng.c uses the permutation table and bit manipulations
  based on the random input to generate pseudo-random numbers.

# Security
No claim is being made as to the security of this software.
Software is provided on an AS-IS basis. Future research is needed.

# Author
Roger Doss
