#!/usr/bin/env bash

passh nodemon -I -w ./build/rgbpng0 -x bash -- -c 'reset && time make rgb-png || true'
