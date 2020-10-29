
DUKTAPE_SOURCES = ../lib/duktape/src/duktape.c
TEST_SOURCE =  ./lib/unity/src/unity.c

CC = gcc
CCOPTS = -Os -pedantic -std=c99 -Wall -fstrict-aliasing -fomit-frame-pointer
CCOPTS += -I../lib/duktape/src -I ./lib/src/unity.h  # for combined sources
CCLIBS = -lm
DEFINES =

# If you want a 32-bit build on a 64-bit host
#CCOPTS += -m32

# Use the tools/configure.py utility to modify Duktape default configuration:
# http://duktape.org/guide.html#compiling
# http://wiki.duktape.org/Configuring.html

# For debugging, use -O0 -g -ggdb, and don't add -fomit-frame-pointer

validate.test: $(DUKTAPE_SOURCES) validate.test.c
	$(CC) -o $@ $(DEFINES) $(CCOPTS) $(DUKTAPE_SOURCES) $(TEST_SOURCE) validate.test.c $(CCLIBS)
