#!/usr/bin/env bash
set -eou pipefail
clear

rm rgb-*.png rgb-*.txt rgb-*.png.c 2>/dev/null || true

./build/rgbpng0

#sleep .1

PNG_FILE="$(\ls rgb-*.png)"
C_PNG_FILE="${PNG_FILE}.c"

kitty +kitten icat $PNG_FILE

./build/cembed0 -o ${C_PNG_FILE} -t rgb_png $PNG_FILE
file $C_PNG_FILE

ansi --yellow --bg-black --italic "$(tail -n 4 $C_PNG_FILE)"
