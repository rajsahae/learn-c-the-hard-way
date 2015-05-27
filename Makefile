CFLAGS=-Wall -g
BIN=bin
SRC=src

EXAMPLES=ex1 ex2 ex3 ex4 ex5 ex6 ex7 ex8 ex9 ex10 ex11 ex12 ex13 ex14 ex15 ex16

all: $(EXAMPLES)

folders: 
	mkdir -p bin

clean:
	rm -rf bin
	rm -rf ex*.dSYM

$(EXAMPLES): folders
	$(CC) $(CFLAGS) -o $(BIN)/$@ $(SRC)/$@.c
