#!/usr/bin/env bash
set -eou pipefail
cd "$(cd $(dirname "${BASH_SOURCE[0]}") && pwd)"
N="$1"
ID="${2:-0}"
SUBDIR="subdir('bins/$N/$ID')"

mkdir -p "$N/$ID"

cp template-meson.build $N/${ID}/meson.build
gsed -i "s|__BIN_NAME__|$N${ID}|g" $N/${ID}/meson.build


egrep -q "^${SUBDIR}$" ../meson.build || \
    echo -e "$SUBDIR" >> ../meson.build

[[ -f "./${N}${ID}.c" ]] && mv "./${N}${ID}.c" $N/$ID/.
