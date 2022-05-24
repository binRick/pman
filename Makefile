default: all
##########################################################
COLORS_QTY = 50
EMBEDDED0_VIEW_QTY = 10
NINJA_CONCURRENCY = 25
ENABLED_BINS_PATTERN= ^katmodule1.*\.c|^assert.*\.c
ENABLED_BINS_PATTERN= ^assert.*\.c|^uptime.*\.c|json.*\.c
ENABLED_DEPS_PATTERN = ^[a-n].*|^[w-z].*|.*fs.*|.*stringbuffer.*|.*occurrences.*|.*stringfn.*|.*uptime.*|.*json.*|parson|.*usb.*|.*socket99.*|.*url.*|.*scriptexec.*|.*md5.*
TIDIED_FILES = bins/*.c src/*module*.c include/*module*.h
##########################################################
ENABLED_DEPS_HASH=etc/enabled-deps-hash.txt
ENABLED_BINS_HASH=etc/enabled-bins-hash.txt
##########################################################
all: \
	build 
##########################################################
PWD=$(shell pwd)
ETC=$(PWD)/etc
BUILD_DIR=$(PWD)/build
INCLUDES_DIR=$(PWD)/include
SCRIPTS_DIR=$(PWD)/scripts
##########################################################
PMAN=$(BUILD_DIR)/pman
PMAN_HELP_CMD=$(PMAN) --help 
FIELD_RANGE_PARSER=$(BUILD_DIR)/field-range-parser
FIND_BINS_CMD = $(SCRIPTS_DIR)/find-bins.sh
FIND_DEPS_CMD = $(SCRIPTS_DIR)/find-deps.sh
##########################################################
PASSH=$(shell command -v passh)
GIT=$(shell command -v git)
SED=$(shell command -v gsed||command -v sed)
NODEMON=$(shell command -v nodemon)
FZF=$(shell command -v fzf)
BLINE=$(shell command -v bline)
##########################################################
COLOR_NAMES_HEADER_FILE = $(INCLUDES_DIR)/embedded-colornames-dev.h
##########################################################
GC=$(GIT) clone --recurse-submodules
GET_COMMIT=$(GIT) log -q |grep '^commit '|head -n1|cut -d' ' -f2
##########################################################
TEST_TITLE=$(BLINE) -a bold:underline:italic:yellow
HELP_STYLE=$(BLINE) -H -a ff00ff
##########################################################
CSV0_IN_FILE = ./etc/colornames.csv
CSV0_OUT_FILE = ./include/embedded-colornames-dev.h
CSV0_CMD = cd $(BUILD_DIR) && ./csv0 -T -i ../$(CSV0_IN_FILE) -o ../$(CSV0_OUT_FILE) -c $(COLORS_QTY) && wc -l ../$(CSV0_OUT_FILE)
##########################################################
EMBEDDED0_CMD = cd $(BUILD_DIR) && { ./embedded0 | tail -n $(EMBEDDED0_VIEW_QTY); }
CEMBED_CMD0 = cd $(BUILD_DIR) && { ./cembed0 -o ../include/embedded-colornames-compiled.h -p __CEMBED_CMD0__ -t __CEMBED_TBL__ -z ../include/embedded-colornames-dev.h && wc -l ../include/embedded-colornames-compiled.h; }
##########################################################
KATMODULE_TEST_TARGETS = \
				   test-katmodule1
COLORS_TEST_TARGETS = \
				   c0 \
				   e0 \
				   ce0
DEV_MAKE_TARGETS = \
				   all \
				   test
DEV_TEST_TARGETS = \
				   $(KATMODULE_TEST_TARGETS)
##########################################################
DEV_CMD =\
		$(PMAN) \
		-t $(PWD)/etc/tpl/color-names/color-names.tpl \
		-i $(PWD)/etc/colornames.csv \
		-o $(PWD)/tmp/colornames.c \
		-c -T 
DEV_CMD_10=\
		$(PMAN) \
		-t $(PWD)/etc/tpl/color-names/color-names.tpl \
		-i $(PWD)/etc/colornames-10.csv \
		-o $(PWD)/tmp/colornames.c \
		-c -T 
##########################################################

all: build

rm-embedded0:
	@unlink $(BUILD_DIR)/embedded0 2>/dev/null||true
	@true

enabled-deps:
	@env ENABLED_DEPS_PATTERN="$(ENABLED_DEPS_PATTERN)" $(FIND_DEPS_CMD)

enabled-bins:
	@env ENABLED_BINS_PATTERN="$(ENABLED_BINS_PATTERN)" $(FIND_BINS_CMD)

pc-cmd:
	@printf '%s\n' "$(DEV_CMD)"

pc-help-cmd:
	@printf '%s\n' "$(PMAN_HELP_CMD)"

pc-help:
	@$(PASSH) $(PMAN_HELP_CMD) | $(HELP_STYLE)

field-range-parser: 
	@eval $(FIELD_RANGE_PARSER)

pc: pc-cmd pc-help
	@eval "$(DEV_CMD_10)"
	@eval "$(DEV_CMD)"

dev: 
	@$(PASSH) -L .nodemon.log $(NODEMON) -I -V -w 'bins/*/*/*.c' -w 'bins/*/*/meson.build' -w 'include/*.h' -w meson -w etc/tpl -w meson.build -w bins -w src -w Makefile -i $(BUILD_DIR) -i submodules -i deps -i 'include/embedded-*.h' -e tpl,build,sh,c,h,Makefile -x env -- bash -c 'make $(DEV_MAKE_TARGETS) $(DEV_TEST_TARGETS)||true'

nodemon:
	@$(PASSH) make

clibs-cmds:
	@./scripts/clib-cmds.sh

submodules-cmds:
	@./scripts/submodules.sh

clibs-install:
	@./scripts/clib-cmds.sh|env bash

submodules-install:
	@./scripts/submodule-cmds.sh|env bash

tools:
	@command -v nodemon || npm i nodemon -g
	@command -v meson || pip install meson

setup: clibs-install submodules-install tools

make-setup:
	@[[ -d deps && -d submodules && -d .venv ]] || make -J 10 setup
	@true

_meson-build:
	@meson $(BUILD_DIR)

meson-build:
	@make _meson-build 2>/dev/null || { make meson-reconfigure 2>/dev/null || make meson-wipe 2>/dev/null || make _meson-build; }
	@true

meson-wipe:
	@meson $(BUILD_DIR) --wipe

meson-reconfigure:
	@{ meson $(BUILD_DIR) --reconfigure 2>/dev/null || { make meson-wipe && make meson-reconfigure; }; } 2>/dev/null || { make meson-wipe && make build; }
	@true

ninja-build:
	@ninja -C build -j $(NINJA_CONCURRENCY)

_build: make-setup meson-build ninja-build

build: enabled-deps enabled-bins _build

#@make _build || { make clean && make _build; }

test:
	@meson test -C $(BUILD_DIR) --verbose

clean:
	@[[ -d $(BUILD_DIR) ]] && rm -rf $(BUILD_DIR) || true
#	@echo '' > $(ENABLED_BINS_HASH)
#	@echo '' > $(ENABLED_DEPS_HASH)
	@true

clean-colors:
	@rm rgb-*.png rgb-*.c 2>/dev/null|| true
	@echo '' > $(COLOR_NAMES_HEADER_FILE)

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


uncrustify:
	@uncrustify -c etc/uncrustify.cfg --replace $(TIDIED_FILES)
	@shfmt -w scripts/*.sh

#	include/*.h src/*.c||true
#src/*.c $(shell find include -type f -name "*.h"|grep -v tmt|grep -v '/embedded-'|tr '\n' ' ')
	
uncrustify-clean:	
	@find . -type f -name "*unc-back*"|xargs -I % unlink %

fix-dbg:
	@gsed 's|, % s);|, %s);|g' -i $(TIDIED_FILES)
	@gsed 's|, % lu);|, %lu);|g' -i $(TIDIED_FILES)
	@gsed 's|, % d);|, %d);|g' -i $(TIDIED_FILES)
	@gsed 's|, % zu);|, %zu);|g' -i $(TIDIED_FILES)

tidy: uncrustify fix-dbg uncrustify-clean

test-katmodule1:
	$(KATMODULE1_CMD)

c0:
	$(CSV0_CMD)

ce0:
	$(CEMBED_CMD0)

e0:
	$(EMBEDDED0_CMD)

colors:
	make c0
	make e0

colors-dev:
	@$(PASSH) -L .colors-dev-nodemon.log $(NODEMON) -I -V -w 'build/*' -w Makefile -i build -i submodules -i deps -i 'include/embedded-*.h' -x /bin/sh -- -c 'make colors||true'

rgb-png:
	@passh timeout 1 ./rgb.sh

rgb-png-dev:
	@passh ./rgb-dev.sh

view-rgb-png:
	@kitty +kitten icat rgb-*.png
