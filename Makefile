CFLAGS=-Wall -g

all: ex1 ex2 ex3 ex4

clean:
	rm -f ex[1-9]
	rm -rf ex*.dSYM
