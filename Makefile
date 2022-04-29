.DEFAULT_GOAL := all


CC = gcc
CFLAGS += -std=gnu99 -O3
CFLAGS += -lm
PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin

VTERM_INCLUDES+=-lvterm

INCLUDES+=./deps/flag/flag.c
INCLUDES+=./deps/b64/*.c
INCLUDES+=./deps/timestamp/*.c
INCLUDES+=./deps/trim/*.c
INCLUDES+=./deps/fs/*.c
INCLUDES+=./deps/list/*.c
INCLUDES+=./deps/parson/parson.c
INCLUDES+=./deps/bytes/bytes.c
INCLUDES+=./deps/rhash_md5/*.c
INCLUDES+=./deps/ms/ms.c
INCLUDES+=./deps/rgba/rgba.c
INCLUDES+=./deps/case/case.c
INCLUDES+=./deps/strsplit/strsplit.c
INCLUDES+=./deps/occurrences/occurrences.c
INCLUDES+=./deps/str-replace/str-replace.c

INCLUDES+=./submodules/csv_parser/csv.c
INCLUDES+=./submodules/csv_parser/split.c
INCLUDES+=./submodules/csv_parser/fread_csv_line.c
INCLUDES+=./submodules/c_string_buffer/src/stringbuffer.c

INCLUDES+=-I include
INCLUDES+=-I src
INCLUDES+=-I submodules
INCLUDES+=-I submodules/c_string_buffer/include
INCLUDES+=-I deps
INCLUDES+=-I .

##################################################
EMBEDDED_PALETTES_FILE=./include/embedded-palettes.h
EMBEDDED_COLORNAMES_FILE=./include/embedded-colornames.h
COLORNAMES_CSV_FILE=./etc/colornames.csv
##################################################
CEMBED=./submodules/cembed/cembed
EMBEDDED_TEMPLATES_TABLE_NAME=__embedded_table__
PALETTE_FILES=
PALETTE_FILES+=$(shell find palettes/dark -type f)
PMAN=bin/pman
TEST_TITLE=bline -a bold:underline:italic:yellow
PASSH=$(shell command -v passh)
SED=$(shell command -v gsed||command -v sed)
PMAN=./bin/pman
NODEMON=$(shell command -v nodemon)
FZF=$(shell command -v fzf)

get_modes:
	@$(PASSH) $(PMAN) --mode modes

get_mode_cmds:
	@$(PASSH) ./bin/pman --mode modes| xargs -I % echo -e "$(PASSH) ./bin/pman --mode %"

cembed_if_expired:
	@make palette_files_hash_not_expired 2>/dev/null || make cembed

all: init cembed src/pman clear test
test: test-pman
cembed: init clean-palette-include cembed-archive write_palette_files_hash assemble-color-names

PALETE_FILES_HASH_FILE=./tmp/palette_files_hash.txt

palette_files_hash:
	@md5sum palettes/dark/*|md5sum|tr '[[:space:]]' '\n'|head -n1

write_palette_files_hash:
	@make palette_files_hash| tee $(PALETE_FILES_HASH_FILE)

palette_files_hash_not_expired:
	@grep -q "^$(shell make palette_files_hash)$$" $(PALETE_FILES_HASH_FILE) 2>/dev/null

test-pman: src/pman

	@echo List Palette Names | $(TEST_TITLE)
	@$(PMAN) --mode palettes;echo

	@echo Help | $(TEST_TITLE)
	@$(PMAN) --help

	@echo Version | $(TEST_TITLE)
	@$(PMAN) --version;echo

	@echo Debug Args | $(TEST_TITLE)
	@$(PMAN) --mode debug_args;echo

	@echo Verbose Debug Args | $(TEST_TITLE)
	@$(PMAN) --mode debug_args --verbose;echo


	@echo View Default Palette | $(TEST_TITLE)
	@$(PMAN) --mode view_palette;echo

	@echo View smyck Palette | $(TEST_TITLE)
	@$(PMAN) --mode view_palette --palette smyck;echo

	@echo Current Palette Colors | $(TEST_TITLE)
	@$(PMAN) --mode cur;echo $?;echo

	@echo Die | $(TEST_TITLE)
	@{ $(PMAN) --mode die;echo $?;echo; } || true

	@echo Message | $(TEST_TITLE)
	@$(PMAN) --mode msg;echo $?;echo

	@echo Error | $(TEST_TITLE)
	@$(PMAN) --mode err;echo $?;echo

	@echo Default Palette Colors | $(TEST_TITLE)
	@$(PMAN) --mode default;echo $?;echo

	@echo Default Palette Properties | $(TEST_TITLE)
	@$(PMAN) --mode default_properties;echo $?;echo

	@echo List Modes | $(TEST_TITLE)
	@$(PMAN) --mode modes;echo

clean-palette-include:
	@truncate --size 0 include/embedded-palettes.h

cembed-build:
	@{ cd submodules/cembed && make; }

unarchive-colornames:
	@cd etc && [[ -f colornames.csv ]] || tar xf colornames.csv.tar.bz2
	@true

generate-colorname-logs:
	@./etc/generate_color_logs.sh

do-assemble-color-names: init unarchive-colornames src/parse_color_names_csv generate-colorname-logs
	@./bin/parse_color_names_csv $(COLORNAMES_CSV_FILE) |tee $(EMBEDDED_COLORNAMES_FILE)|pv -l >/dev/null

nullify-colornames: 
	@cat include/embedded-colornames-base.h > include/embedded-colornames.h

assemble-color-names: init nullify-colornames do-assemble-color-names

cembed-archive: init
	@eval $(CEMBED) -t $(EMBEDDED_TEMPLATES_TABLE_NAME) -o $(EMBEDDED_PALETTES_FILE) $(PALETTE_FILES)

init:
	@mkdir -p bin tmp etc/color-logs

rm:
	@rm -rf bin tmp

rmrf: rm
	@rm -rf etc/color-logs

clean: rm clean-palette-include nullify-colornames
	@$(SED) -i 's|, % |, %|g' src/*.c


clear:
	@clear

tidy:
	@uncrustify -c etc/uncrustify.cfg --replace src/*.c $(shell find include -type f -name "*.h"|grep -v '/embedded-'|tr '\n' ' ') scripts/*.sh
	@find . -type f -name "*unc-back*"|xargs -I % unlink %

dev-fzf-modes:
	@$(NODEMON) -w palettes -w bin/pman -I -x env -- sh -c 'make fzf-modes'

fzf-modes:
	@clear; make get_modes| env SHELL=/bin/sh \
		$(FZF) \
		--color "fg:#bbccdd,fg+:#ddeeff,bg:#334455,preview-bg:#223344,border:#778899" \
		--preview-window "right,50%,border-horizontal,border-vertical" \
		--ansi \
		--header "Select an Execution Mode" \
		--info inline \
		--border \
		--header-lines=0 --header-first \
		--height 100% \
		--layout=reverse \
		--preview "ansi --bold --bg-black --yellow '{}' && echo && eval $(PASSH) $(PMAN) --mode '{}'; echo;echo; ansi --bold --blue Exit Code: $$?"

nodemon: init cembed 
	@make -j 10 __nodemon
#	@make src/parse_color_names_csv
#	@make assemble-color-names 
#	@make cembed
#	@make src/parse_color_names_csv
#	@make src/pman
__nodemon: 
	@make -j 10 srcs
	@make test

srcs: do-srcs

do-srcs: 
	make -j 10 src/pman src/parse_color_names_csv src/vterm

dev:
	@$(PASSH) -L .nodemon.log $(NODEMON) -w src -w . -w Makefile -i submodules -i deps -i 'include/embedded-*.h' -e sh,c,h,Makefile -x env -- bash -c 'make nodemon||true'

src/vterm: src/vterm.c
	$(CC) $(CFLAGS) -o ./bin/$(shell basename $@) $< $(LDFLAGS) $(INCLUDES) $(VTERM_INCLUDES)

src/parse_color_names_csv: src/parse_color_names_csv.c
	@make init
	$(CC) $(CFLAGS) -o ./bin/$(shell basename $@) $< $(LDFLAGS) $(INCLUDES)

src/pman: src/pman.c
	@make init
	$(CC) $(CFLAGS) -o ./bin/$(shell basename $@) $< $(LDFLAGS) $(INCLUDES)

install: all
	install -Dm755 pman $(DESTDIR)$(BINDIR)/pman
	mkdir -p $(DESTDIR)/usr/local/share/pman
	cp -r palettes $(DESTDIR)/usr/local/share/pman

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/pman
	rm -rf $(DESTDIR)/usr/local/share/pman

clib:
	clib i -c

.PHONY: all install uninstall clean
