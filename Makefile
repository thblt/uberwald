CC=clang
CFLAGS=-W -Wall -std=c11 -pedantic
LDFLAGS=
SRC = src/cli.c src/eval.c src/eval.c src/ltypes.c src/read.c src/stack.c src/uberwald.c
OBJ = $(SRC:.c=.o)
CLISRC = $(SRC) src/cli.c
CLIOBJ = $(CLISRC:.c=.o)
TESTSRC=$(wildcard tests/*.c) # $(SRC)
TESTOBJ = $(TESTSRC:.c=.o)

EXEC=uberwald

all:

uberwald: $(CLIOBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

test: $(TESTOBJ)
	$(CC) -lcheck -o $@ $^  $(LDFLAGS)

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@rm -rf src/*.o tests/*.o uberwald
