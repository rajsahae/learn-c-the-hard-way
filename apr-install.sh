#!/bin/sh

set -e

# go somewhere safe
cd ~/src

# get the source to base APR 1.4.6
curl -L -O http://archive.apache.org/dist/apr/apr-1.4.6.tar.gz

tar -xzvf apr-1.4.6.tar.gz
cd apr-1.4.6

# configure, make, make install
./configure
make
sudo make install

# reset and cleanup
cd ~/src
# rm -rf apr-1.4.6*

# install apr-util
curl -L -O http://archive.apache.org/dist/apr/apr-util-1.4.1.tar.gz

# extract
tar -xvzf apr-util-1.4.1.tar.gz
cd apr-util-1.4.1

# configure, make, make install
./configure --with-apr=/usr/local/apr

make
sudo make install

# cleanup
cd ~/src
# rm -rf apr-util-1.4.1* apr-1.4.6*
