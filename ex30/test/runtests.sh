#!/bin/sh

LOGFILE=test/test.log

echo "Running unit tests:"

for i in test/*_test; do
  if test -f $i; then
    if $VALGRIND ./$i 2>> $LOGFILE; then
      echo "PASS: $i"
    else
      echo "ERROR: $i"
      echo "------"
      tail $LOGFILE
      exit 1
    fi
  fi
done

echo ""
