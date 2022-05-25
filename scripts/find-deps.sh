#!/usr/bin/env bash
set -eou pipefail
cd "$(cd $(dirname "${BASH_SOURCE[0]}") && pwd)"
if ! command -v gsed >/dev/null; then alias gsed=sed; fi
DEFAULT_ENABLED_DEPS_PATTERN='^.*|^[a-z].*'

ENABLED_DEPS_HASH_FILE=$(cd ../. && pwd)/etc/enabled-deps-hash.txt
DEPS_DIR_NAME=meson/deps
DEPS_DIR=$(cd ../. && pwd)/$DEPS_DIR_NAME
MAKEFILE=$(cd ../. && pwd)/Makefile
ENABLED_DEPS_PATTERN="${ENABLED_DEPS_PATTERN:-${DEFAULT_ENABLED_DEPS_PATTERN}}/meson.build$"
[[ -f "$ENABLED_DEPS_HASH_FILE" ]] || touch "$ENABLED_DEPS_HASH_FILE"

md5() {
	md5sum | cut -d' ' -f1
}

dep_files() {
	(cd ${DEPS_DIR} && \find . -type f -name meson.build | \gsed 's/^\.\///g' | sort -u)
}

enabled_dep_files() {
	\egrep "$ENABLED_DEPS_PATTERN" < <(dep_files)
}

enabled_dep_dirs() {
	enabled_dep_files | xargs -I % dirname % | while read -r d; do echo "./${DEPS_DIR_NAME}/${d}"; done
}

enabled_dep_files_hash() {
	{
		enabled_dep_files
		enabled_dep_files | xargs -I % md5sum ${DEPS_DIR}/%
	} | md5
}

make_clean() {
	make -C "$(dirname $MAKEFILE)" clean
}

handle_expired_deps_hash() {
	#make_clean
	enabled_dep_files_hash >$ENABLED_DEPS_HASH_FILE
	ansi >&2 --green --bold "deps hash updated"
}

main() {
	ed="$(enabled_dep_dirs)"
	ed_hash="$(enabled_dep_files_hash)"
	ansi >&2 --blue --bold "$ed_hash"
	if \grep -q "^${ed_hash}" "$ENABLED_DEPS_HASH_FILE"; then
		ansi >&2 --green --bold "OK deps hash :: $ed_hash"
	else
		ansi >&2 --red --bold "expired deps hash :: $(\cat $ENABLED_DEPS_HASH_FILE) => $ed_hash"
		handle_expired_deps_hash
	fi
	echo -e "$ed"
}

dev() {
	dep_files
	echo
	enabled_dep_files
	echo
	enabled_dep_files_hash
	echo
}

main
