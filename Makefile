CFLAGS=-Wall -g
BIN=bin

all: ex1 ex2 ex3 ex4 ex5

clean:
	rm -f ex[1-9]
	rm -rf ex*.dSYM

ex1:
	$(CC) $(CFLAGS) -o $(BIN)/ex1 ex1.c

ex2:
	$(CC) $(CFLAGS) -o $(BIN)/ex2 ex2.c

ex3:
	$(CC) $(CFLAGS) -o $(BIN)/ex3 ex3.c

ex4:
	$(CC) $(CFLAGS) -o $(BIN)/ex4 ex4.c

ex5:
	$(CC) $(CFLAGS) -o $(BIN)/ex5 ex5.c
