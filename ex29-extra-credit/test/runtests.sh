#!/bin/sh

set -e

echo "Running unit tests:"

./test/ex29_test ./build/libex29.so print_a_message "hello there"
./test/ex29_test ./build/libex29.so uppercase "hello there" 11
./test/ex29_test ./build/libex29.so lowercase "HELLO tHeRe" 11
! ./test/ex29_test ./build/libex29.so fail_on_purpose "i fail"
! ./test/ex29_test ./build/libex29.so fail_on_purpose
! ./test/ex29_test ./build/libex29.so adfasfasdf asdfadff
! ./test/ex29_test ./build/libex.so adfasfasdf asdfadfas

echo "All tests passed"
