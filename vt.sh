make src/vt
vterm-ctrl reset
env bash -c 'ansi -n --bold KK; ansi --bell; ansi --hide-cursor; ansi --column=5 --bold KK; ansi --reset; echo;echo;ansi --column=5 KK' | ./bin/vt|grep K
