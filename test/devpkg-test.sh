#!/bin/bash

cleanup() {
  rm -rf /usr/local/.devpkg
  rm -rf /tmp/pkg*
  rm -f /usr/local/bin/curl
}

# Clean before we start
cleanup

set -e

# Make sure to run from the devpkg project root folder
EXE=./devpkg
URL='https://github.com/bagder/curl/releases/download/curl-7_43_0/curl-7.43.0.tar.gz'

# Initialize devpkg db
$EXE -S

# Fetch a package
$EXE -F $URL

# Install a package
$EXE -I $URL

# List the package
$EXE -L | grep $URL

# Install should fail
! $EXE -I $URL

# Build should happen anyway
$EXE -B $URL

# Cleanup
cleanup
