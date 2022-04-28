CC     ?= gcc
CFLAGS += -std=gnu99 -O3
PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin

INCLUDES=
INCLUDES+=./deps/flag/flag.c
INCLUDES+=./deps/b64/*.c
INCLUDES+=./deps/timestamp/*.c
INCLUDES+=./deps/trim/*.c
INCLUDES+=./deps/list/*.c
INCLUDES+=./deps/parson/parson.c
INCLUDES+=./deps/bytes/bytes.c
INCLUDES+=./deps/rhash_md5/*.c
INCLUDES+=./deps/ms/ms.c
INCLUDES+=./deps/rgba/rgba.c
INCLUDES+=./deps/strsplit/strsplit.c

INCLUDES+=-I include
INCLUDES+=-I src
INCLUDES+=-I submodules
INCLUDES+=-I deps
INCLUDES+=-I .

CEMBED=./submodules/cembed/cembed
CEMBED_FILE=./include/embedded-palettes.h
EMBEDDED_TEMPLATES_TABLE_NAME=__embedded_table__
PALETTE_FILES=
PALETTE_FILES+=$(shell find palettes/dark -type f)
KFC=bin/pman
TEST_TITLE=bline -a bold:underline:italic:yellow

cembed: init clean-palette-include assemble-palettes cembed-archive
all: init cembed src/pman clear test
test: test-pman

test-pman:
	@echo List Palette Names | $(TEST_TITLE)
	@$(KFC) --mode palettes;echo
	@echo Help | $(TEST_TITLE)
	@$(KFC) --help
	@echo Version | $(TEST_TITLE)
	@$(KFC) --version;echo
	@echo Debug Args | $(TEST_TITLE)
	@$(KFC) --mode debug_args;echo
	@echo Verbose Debug Args | $(TEST_TITLE)
	@$(KFC) --mode debug_args --verbose;echo
	@echo List Modes | $(TEST_TITLE)
	@$(KFC) --mode list_modes;echo
	@echo View Default Palette | $(TEST_TITLE)
	@$(KFC) --mode view_palette;echo
	@echo View smyck Palette | $(TEST_TITLE)
	@$(KFC) --mode view_palette --palette smyck;echo
	@echo Current Palette Colors | $(TEST_TITLE)
	@$(KFC) --mode cur;echo $?;echo
	@echo Die | $(TEST_TITLE)
	@{ $(KFC) --mode die;echo $?;echo; } || true
	@echo Message | $(TEST_TITLE)
	@$(KFC) --mode msg;echo $?;echo
	@echo Error | $(TEST_TITLE)
	@$(KFC) --mode err;echo $?;echo

clean-palette-include:
	@rm -rf include/embedded-palettes.h

cembed-build:
	@{ cd submodules/cembed && make; }

assemble-palettes: init
	@rm -rf tmp/palettes||true
	@mkdir -p tmp/palettes
	@cp -prf palettes tmp/palettes/pman

cembed-archive: assemble-palettes
	@$(CEMBED) -t $(EMBEDDED_TEMPLATES_TABLE_NAME) -o $(CEMBED_FILE) $(PALETTE_FILES)

init:
	@mkdir -p bin tmp

clean:
	@rm -rf bin tmp include/embedded-palettes.h

clear:
	@clear

tidy:
	@uncrustify -c etc/uncrustify.cfg --replace src/*.c $(shell find include -type f -name "*.h"|grep -v '/embedded-'|tr '\n' ' ')
	@find . -type f -name "*unc-back*"|xargs -I % unlink %

dev:	
	passh -L .nodemon.log nodemon -w . -w Makefile -i submodules -i deps -i include/embedded-palettes.h -e sh,c,h,Makefile -x sh -- -c 'make all test||true'

src/pman: src/pman.c Makefile
	$(CC) -O3 $(CFLAGS) -o ./bin/$(shell basename $@) $< -lX11 $(LDFLAGS) $(INCLUDES)

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
