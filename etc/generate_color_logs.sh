#!/usr/bin/env bash
set -eou pipefail
cd "$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
LIMIT=${1:-9999999}

THIS_SCRIPT="$(pwd)/$(basename ${BASH_SOURCE[0]})"
CMDS_FILE=$(pwd)/.color-cmds.sh
CMDS_HASH_FILE=$(pwd)/.color-cmds-hash-$(date +%Y%m%d)-$LIMIT.txt
COLOR_LOGS_DIR=$(pwd)/color-logs
COLOR_NAMES_CSV_FILE=$(pwd)/colornames.csv
PALETTES_DIR=$(pwd)/../palettes
CCC=$(pwd)/bin/ccc
cat=$(command -v cat)

init() {
	[[ -d $PALETTES_DIR ]] || mkdir -p $PALETTES_DIR
	[[ -d $COLOR_LOGS_DIR ]] || mkdir -p $COLOR_LOGS_DIR
	[[ -f $COLOR_NAMES_CSV_FILE ]] || {
		ansi --red missing $COLOR_NAMES_CSV_FILE
		exit 1
	}
}

filter() {
	grep -E -o '[[:xdigit:]]{6}'
}

uppercase() {
	tr '[a-z]' '[A-Z]'
}

normalize_names() {
	cut -d'#' -f2 | uppercase | dos2unix
}

names() {
	head -n $LIMIT $COLOR_NAMES_CSV_FILE
}

_pv() {
	\pv -l >/dev/null
}

palette_files() {
	find $PALETTES_DIR/*/* -type f
}

palette_colors() {
	palette_files | xargs -I % cat % | cut -d'=' -f2 | tr '[a-z]' '[A-Z]' | dos2unix | sort -u | grep -E -o '[[:xdigit:]]{6}' | sort -u
}

color_codes() {
	{
		names | normalize_names
		palette_colors
	} | uppercase | filter | sort -u
}

codes_to_cmds() {
	while read -r _l; do
		echo -e "bin/ccc -I x=$_l -s -V | tee $COLOR_LOGS_DIR/$_l"
	done
}

generate_cmds() {
	color_codes | codes_to_cmds
}

get_hash() {
	{
		md5sum <$THIS_SCRIPT
		md5sum <$COLOR_NAMES_CSV_FILE
		md5sum <$CCC
		find $PALETTES_DIR -type f | md5sum
		find $COLOR_LOGS_DIR -type f | md5sum
	} | md5sum | cut -d' ' -f1
}

write_hash() {
	get_hash | tee $CMDS_HASH_FILE
}

hash_is_expired() {
	[[ -f $CMDS_HASH_FILE ]] || return 0
	if grep -q "^$(get_hash)$" $CMDS_HASH_FILE; then
		echo >&2 hash OK
		ec=1
	else
		echo >&2 hash EXPIRED
		ec=0
	fi
	return $ec
}

write_cmds() {
	generate_cmds | tee $CMDS_FILE | _pv
}

run_cmds() {
	rm -rf $COLOR_LOGS_DIR
	init
	time bash $CMDS_FILE | _pv
}

qty() {
	find $COLOR_LOGS_DIR -type f | wc -l
}

run_cmds_if_expired_hash() {
	if hash_is_expired; then
		write_cmds
		run_cmds
		write_hash
		ec=$?
	else
		ec=0
	fi
	return $ec
}

atexit() {
	ansi --yellow --bold --italic "$(ansi --green --inverse --bold $(qty)) Color log files @ $COLOR_LOGS_DIR | \
 Hash: $(ansi --blue --bg-black --bold --inverse $(get_hash))"
}

main() {
	init
	trap atexit EXIT
	ansi --yellow --bold --italic "$(color_codes | wc -l) Color Codes @ $(ansi --blue --bold --inverse $COLOR_NAMES_CSV_FILE)"
	ansi --yellow --bold --italic "Current Hash: $(ansi --red --bold --inverse $(get_hash)) @ $(ansi --magenta --bold --inverse $CMDS_HASH_FILE)"
	run_cmds_if_expired_hash
}

main
