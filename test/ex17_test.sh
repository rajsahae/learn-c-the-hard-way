#!/bin/sh

# Exit on any error
set -e

# Clean out existing test db's
rm -vf db.dat

# Test creation
bin/ex17 db.dat c

# Test setting empty rows
bin/ex17 db.dat s 1 raj test@raj.com
bin/ex17 db.dat s 2 dana test@dana.com
bin/ex17 db.dat s 3 natalie test@natalie.com
bin/ex17 db.dat s 9 randy test@randy.com

# Test setting occupied rows
! bin/ex17 db.dat s 2 bob foo@bar.com

# Test listing all rows
bin/ex17 db.dat l

# Test getting occupied rows
bin/ex17 db.dat g 1
bin/ex17 db.dat g 2
bin/ex17 db.dat g 3
bin/ex17 db.dat g 9

# Test getting empty rows
! bin/ex17 db.dat g 5
! bin/ex17 db.dat g 10

# Test deleting empty rows
bin/ex17 db.dat d 5
bin/ex17 db.dat d 10

# Test deleting occupied rows
! bin/ex17 db.dat d 2
! bin/ex17 db.dat d 9

# Clean up after ourselves
rm -vf db.dat

echo All tests passed
