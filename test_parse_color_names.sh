#!/usr/bin/env bash
set -eou pipefail
cat include/embedded-colornames-base.h > include/embedded-colornames.h
make src/parse_color_names_csv

cd ./etc/color-logs
set -x
../../bin/parse_color_names_csv ../colornames.csv | tee ../../include/embedded-colornames.h | pv -l >/dev/null



