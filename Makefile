default: all
##########################################################
all: \
	build \
	test
##########################################################
PWD="$(shell pwd)"
BUILD_DIR=$(PWD)/build
##########################################################
PMAN=$(BUILD_DIR)/pman
##########################################################
GC=$(GIT) clone --recurse-submodules
GET_COMMIT=$(GIT) log -q |grep '^commit '|head -n1|cut -d' ' -f2
##########################################################
PASSH=$(shell command -v passh)
GIT=$(shell command -v git)
SED=$(shell command -v gsed||command -v sed)
NODEMON=$(shell command -v nodemon)
FZF=$(shell command -v fzf)
BLINE=$(shell command -v bline)
##########################################################
TEST_TITLE=$(BLINE) -a bold:underline:italic:yellow
HELP_STYLE=$(BLINE) -H -a ff00ff
##########################################################
DEV_MAKE_TARGETS = \
				   all
DEV_TEST_TARGETS = \
				   pc
##########################################################
PMAN_HELP_CMD=$(PMAN) --help 
DEV_CMD=\
		$(PMAN) \
		-t tmp/color-names0.tpl \
		-i tmp/colornames.csv \
		-o tmp/colornames.c \
		-r -T -v
##########################################################


pc-cmd:
	@printf '%s\n' "$(DEV_CMD)"

pc-help-cmd:
	@printf '%s\n' "$(PMAN_HELP_CMD)"

pc-help:
	@$(PASSH) $(PMAN_HELP_CMD) | $(HELP_STYLE)

pc: pc-cmd pc-help
	@eval "$(DEV_CMD)"

dev: 
	@$(PASSH) -L .nodemon.log $(NODEMON) -I -V -w etc/tpl -w meson.build -w bins -w src -w Makefile -i build -i submodules -i deps -i 'include/embedded-*.h' -e tpl,build,sh,c,h,Makefile -x env -- bash -c 'make $(DEV_MAKE_TARGETS) $(DEV_TEST_TARGETS)||true'

nodemon:
	@$(PASSH) make

dependencies: base252 objectively

clibs-cmds:
	@./scripts/clib-cmds.sh

submodules-cmds:
	@./scripts/submodules.sh

clibs-install:
	@./scripts/clib-cmds.sh|env bash

submodules-install:
	@./scripts/submodule-cmds.sh|env bash

setup: dependencies clibs-install submodules-install tools

tools:
	@command -v nodemon || npm i nodemon -g
	@command -v meson || pip install meson

build: 
	@[[ -d deps && -d submodules && -d .venv ]] || make -J 10 setup
	@test -d $(BUILD_DIR) && {  meson $(BUILD_DIR) --reconfigure; } || { meson $(BUILD_DIR); }
	@ninja -C build

test:
	@meson test -C $(BUILD_DIR) --verbose

clean:
	@test -d $(BUILD_DIR) && rm -rf $(BUILD_DIR)

install:
	@echo Install OK

pull: git-pull clib build test

clib-update:
	@./update_commit.sh

objectively:
	@[[ -d deps/Objectively ]] || $(GC) https://github.com/jdolan/Objectively deps/Objectively
	@cd deps/Objectively && git pull
	@cd deps/Objectively && [[ -f configure ]] || autoreconf -i
	@cd deps/Objectively && [[ -f Makefile ]] || ./configure
	@cd deps/Objectively && make -j

base252:
	@[[ -d deps/base252 ]] || $(GC) https://github.com/scandum/base252 deps/base252
	@cd deps/base252 && git pull
#	@cd deps/base252 && gcc -lz -o test test.c && ./test

git-pull:
	@git pull

git-commit:
	@git commit -am 'automated git commit'

push: tidy git-commit
	@git push


do-bins: make-bins

tidy:
	@uncrustify -c etc/uncrustify.cfg --replace bins/*.c src/*.c $(shell find include -type f -name "*.h"|grep -v '/embedded-'|tr '\n' ' ')
	@shfmt -w scripts/*.sh
	@find . -type f -name "*unc-back*"|xargs -I % unlink %

