#! /usr/bin/env bash
set - eou pipefail


cd $(dirname "${BASH_SOURCE[0]}")

cd../.
  make test
