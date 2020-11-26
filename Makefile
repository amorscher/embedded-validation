
DUKTAPE_SOURCES = lib/duktape/src/duktape.c
DUKTAPE_V1_COMAPT_SOURCES = lib/duktape/extras/duk-v1-compat/duk_v1_compat.c

CC = gcc
CCOPTS = -Os -pedantic -std=c99 -Wall -fstrict-aliasing -fomit-frame-pointer
CCOPTS += -I./lib/duktape/src  -I./lib/duktape/extras/duk-v1-compat -I./src # for combined sources
CCLIBS = -lm
DEFINES =
OUTDIR = bin/
EXECUTEABLE = validate

# If you want a 32-bit build on a 64-bit host
#CCOPTS += -m32

# Use the tools/configure.py utility to modify Duktape default configuration:
# http://duktape.org/guide.html#compiling
# http://wiki.duktape.org/Configuring.html

# For debugging, use -O0 -g -ggdb, and don't add -fomit-frame-pointer

$(EXECUTEABLE): $(DUKTAPE_SOURCES) src/validate.c
	$(CC) -o $(OUTDIR)$@ $(DEFINES) $(CCOPTS) $(DUKTAPE_SOURCES)  $(DUKTAPE_V1_COMAPT_SOURCES) src/validate.c src/main.c $(CCLIBS)

clean:
	rm -rf $(OUTDIR)$(EXECUTEABLE);