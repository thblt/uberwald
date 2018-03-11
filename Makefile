CC=clang
CFLAGS=-W -Wall -std=c11 -pedantic -D_UBERWALD_INTERNALS
LDFLAGS=-lreadline
SRC = src/eval.c src/object.c src/read.c src/stack.c src/store.c
OBJ = $(SRC:.c=.o)
CLISRC = $(SRC) src/cli.c
CLIOBJ = $(CLISRC:.c=.o)
TESTSRC=$(wildcard tests/*.c) $(SRC)
TESTOBJ = $(TESTSRC:.c=.o)

EXEC=uberwald

all: uberwald

uberwald: $(CLIOBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

test: $(TESTOBJ)
	$(CC) -lcheck -o $@ $^  $(LDFLAGS)

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@rm -rf src/*.o tests/*.o uberwald test

.PHONY: clean check

check: test
	@./test
