BUILD_DIR = ./build
GC = git clone --recurse-submodules
GET_COMMIT = "git log -q |grep '^commit '|head -n1|cut -d' ' -f2"
TEST_TITLE=bline -a bold:underline:italic:yellow
PASSH=$(shell command -v passh)
SED=$(shell command -v gsed||command -v sed)
PMAN=./bin/pman
NODEMON=$(shell command -v nodemon)
FZF=$(shell command -v fzf)

default: all

.PHONY: all

all: build test

.PHONY: .FORCE
.FORCE:

dependencies: base252 objectively

submodules-cmds:
	@./scripts/submodules.sh

submodules-install:
	@./scripts/submodules.sh|env bash

clib-install:
	@clib install -c || ./scripts/clib-install.sh

setup: clib-install submodules-install
	@command -v nodemon || npm i nodemon -g
	@command -v meson || pip install meson

build: dependencies
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



nodemon:
	@$(PASSH) make exec-bins-gccs-args

do-bins: make-bins

dev: 
	@$(PASSH) -L .nodemon.log $(NODEMON) -V -w etc/tpl -w meson.build -w bins -w src -w Makefile -i build -i submodules -i deps -i 'include/embedded-*.h' -e tpl,build,sh,c,h,Makefile -x env -- bash -c 'make||true'

tidy:
	@uncrustify -c etc/uncrustify.cfg --replace bins/*.c src/*.c $(shell find include -type f -name "*.h"|grep -v '/embedded-'|tr '\n' ' ')
	@shfmt -w scripts/*.sh
	@find . -type f -name "*unc-back*"|xargs -I % unlink %

