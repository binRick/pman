#!/usr/bin/env bash
set -eou pipefail
cd "$(cd $(dirname "${BASH_SOURCE[0]}") && pwd)"

rsync -ar ../submodules .
rsync -ar ../deps .

docker build . -t pman --target pman
