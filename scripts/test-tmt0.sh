#!/usr/bin/env bash
vterm-ctrl reset
(
	ansi -n --hide-cursor
	ansi --position=2,4 -n 2x4
	ansi -n --faint faint-on
	ansi -n --normal faint-off
	ansi -n --bold bold-on
	ansi -n --normal bold-off
	ansi --reset -n
	ansi --hide-cursor cursor -n off
	ansi --show-cursor cursor -n on
	ansi -n --bell --bell
	ansi --position=1,1 -n 1x1
	ansi --position=2,2 -n 2x2
	ansi --position=1,5 -n 1x5
	ansi --position=1,10 -n 1x10
	ansi --position=2,15 -n --bold --faint --reverse 2x15
	ansi -n --position=3,5 --bold --faint --reverse 3x5
	ansi -n --position=3,10 --bold --faint --reverse 3x10
	ansi -n --position=3,18 --bold --faint --reverse 3x18
) | ./tmt0 2>&1
