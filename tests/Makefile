
DUKTAPE_SOURCES = ../lib/duktape/src/duktape.c
DUKTAPE_V1_COMAPT_SOURCES = ../lib/duktape/extras/duk-v1-compat/duk_v1_compat.c
ITEM_UNDER_TEST = ../src/validate.c
TEST_SOURCE =  ./lib/unity/src/unity.c

CC = gcc
CCOPTS = -Os -pedantic -std=c99 -Wall -fstrict-aliasing -fomit-frame-pointer
CCOPTS += -I../lib/duktape/src -I ./lib/src/unity.h -I ../lib/duktape/extras/duk-v1-compat -I../src # for combined sources
CCLIBS = -lm
DEFINES =

# If you want a 32-bit build on a 64-bit host
#CCOPTS += -m32

# Use the tools/configure.py utility to modify Duktape default configuration:
# http://duktape.org/guide.html#compiling
# http://wiki.duktape.org/Configuring.html

# For debugging, use -O0 -g -ggdb, and don't add -fomit-frame-pointer

test, all: validate.test
	@./validate.test

clean:
	rm -rf validate.test

validate.test: $(DUKTAPE_SOURCES) validate.test.c
	$(CC) -o $@ $(DEFINES) $(CCOPTS) $(DUKTAPE_SOURCES) $(TEST_SOURCE) $(DUKTAPE_V1_COMAPT_SOURCES) $(ITEM_UNDER_TEST) validate.test.c $(CCLIBS)
