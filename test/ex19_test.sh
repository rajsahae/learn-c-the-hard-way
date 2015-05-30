#!/bin/sh

# Exit on any error
set -e

commands="l\na\ns\nw\ne\nn\nl\nn\na\ne\ne\nl\na\nw\nw\nl\na\na\na\na\na\na\na\na\na\na\n"

# Run the game
echo $commands | bin/ex19

echo All tests passed
