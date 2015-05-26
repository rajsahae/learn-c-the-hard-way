CFLAGS=-Wall -g
BIN=bin
SRC=src

all: ex1 ex2 ex3 ex4 ex5 ex6

clean:
	rm -rf bin
	rm -rf ex*.dSYM

ex1:
	$(CC) $(CFLAGS) -o $(BIN)/ex1 $(SRC)/ex1.c

ex2:
	$(CC) $(CFLAGS) -o $(BIN)/ex2 $(SRC)/ex2.c

ex3:
	$(CC) $(CFLAGS) -o $(BIN)/ex3 $(SRC)/ex3.c

ex4:
	$(CC) $(CFLAGS) -o $(BIN)/ex4 $(SRC)/ex4.c

ex5:
	$(CC) $(CFLAGS) -o $(BIN)/ex5 $(SRC)/ex5.c

ex6:
	$(CC) $(CFLAGS) -o $(BIN)/ex6 $(SRC)/ex6.c
