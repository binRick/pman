#!/usr/bin/env bash
set -eou pipefail
cd "$(cd $(dirname "${BASH_SOURCE[0]}") && pwd)"
ENABLED_BINS_HASH_FILE=$(cd ../. && pwd)/etc/enabled-bins-hash.txt
BINS_DIR=$(cd ../. && pwd)/bins
MAKEFILE=$(cd ../. && pwd)/Makefile
DEFAULT_ENABLED_BINS_PATTERN='^[a-z].*[0-9].*\.c$'
ENABLED_BINS_PATTERN="${ENABLED_BINS_PATTERN:-${DEFAULT_ENABLED_BINS_PATTERN}}"
[[ -f "$ENABLED_BINS_HASH_FILE" ]] || touch "$ENABLED_BINS_HASH_FILE"

md5() {
	md5sum | cut -d' ' -f1
}

meson_build_files(){
    find "${BINS_DIR}" -type f -name meson.build
}

bin_c_files() {
	\grep 'MESON_BIN_ENABLED=true' $BINS_DIR/*.c | \cut -d: -f1 | \xargs -I % \basename % | \sort -u
}

enabled_c_files() {
	\egrep "$ENABLED_BINS_PATTERN" < <(bin_c_files)
}

enabled_bins() {
	xargs -I % \basename % .c < <(enabled_c_files)
}

enabled_c_files_hash() {
	{
		enabled_c_files
		enabled_c_files | xargs -I % md5sum ${BINS_DIR}/%
	} | md5
}

make_clean() {
	make -C "$(dirname $MAKEFILE)" clean
}

handle_expired_bins_hash() {
	#make_clean
	enabled_c_files_hash >$ENABLED_BINS_HASH_FILE
	ansi >&2 --green --bold "bins hash updated"
}

main() {
	eb="$(enabled_bins)"
	eb_hash="$(enabled_c_files_hash)"
	ansi >&2 --blue --bold "$eb_hash"
	if \grep -q "^${eb_hash}" "$ENABLED_BINS_HASH_FILE"; then
		ansi >&2 --green --bold "OK bins hash :: $eb_hash"
	else
		ansi >&2 --red --bold "expired bins hash :: $(\cat $ENABLED_BINS_HASH_FILE) => $eb_hash"
		handle_expired_bins_hash
	fi
	echo -e "$eb"
}

main
