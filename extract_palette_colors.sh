#!/usr/bin/env bash
set -eou pipefail
cd "$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

cat palettes/*/*|cut -d'=' -f2|tr '[a-z]' '[A-Z]'|dos2unix|sort -u|grep -E -o '[[:xdigit:]]{6}'|sort -u
