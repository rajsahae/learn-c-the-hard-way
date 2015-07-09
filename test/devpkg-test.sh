#!/bin/bash

cleanup() {
  echo "Cleaning up"
  rm -rf /usr/local/.devpkg
  rm -rf /tmp/pkg*
  rm -f /usr/local/bin/curl
}

# Clean before we start
cleanup

set -e

# Make sure to run from the devpkg project root folder
EXE=devpkg/devpkg
URL='https://github.com/bagder/curl/releases/download/curl-7_43_0/curl-7.43.0.tar.gz'

# Initialize devpkg db
echo "Initializing devpkg"
$EXE -S

# Fetch a package
echo "Testing fetch"
$EXE -F $URL

# Install a package
echo "Testing install"
$EXE -I $URL

# List the package
echo "Testing list"
$EXE -L | grep $URL

# Install should fail
echo "Testing failed install"
! $EXE -I $URL

# Build should happen anyway
echo "Testing build"
$EXE -B $URL

# Cleanup
cleanup

echo
echo devpkg: All tests passed
echo
