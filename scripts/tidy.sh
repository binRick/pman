#! /usr/bin/env bash
set - eou pipefail


cd $(cd "$(dirname "$ { BASH_SOURCE[0] } ")" && pwd)

cd../.
  make tidy
