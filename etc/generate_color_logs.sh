#!/usr/bin/env bash
set -eou pipefail
cd "$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
LIMIT=${1:-9999999}
[[ -d color-logs ]] && rm -rf color-logs
mkdir color-logs

regex() {
	[[ $1 =~ $2 ]] && printf '%s\n' "${BASH_REMATCH[1]}"
}

trim_all() {
	set -f
	set -- $*
	printf '%s\n' "$*"
	set +f
}

filter() {
	grep -E -o '[[:xdigit:]]{6}'
}

gl() {
	cut -d'#' -f2 | tr '[a-z]' '[A-Z]' | dos2unix
}

names() {
	head -n $LIMIT colornames.csv
}

_pv() {
	\pv -l >/dev/null
}

palette_colors(){
    ../extract_palette_colors.sh
}

color_codes() {
    {
        names | gl
        palette_colors
    } | filter
}

codes_to_cmds() {
	while read -r _l; do
		echo -e "bin/ccc -I x=$_l -s -V | tee color-logs/$_l"
	done
}

generate_cmds() {
	color_codes | codes_to_cmds
}

write_cmds() {
	generate_cmds | tee cmds.sh | _pv
}

run_cmds() {
	time bash cmds.sh | _pv
}

qty(){
    find color-logs -type f | wc -l
}

main() {
	write_cmds
	run_cmds
}

#color_codes
main


ansi --yellow --bold --italic "Wrote $(qty) Color log files!"

