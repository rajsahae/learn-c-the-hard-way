CFLAGS=-Wall -g
BIN=bin
SRC=src

all: ex1 ex2 ex3 ex4 ex5 ex6 ex7 ex8 ex9 ex10 ex11 ex12 ex13 ex14 ex15 ex16

folders: 
	mkdir -p bin

clean:
	rm -rf bin
	rm -rf ex*.dSYM

ex1: folders
	$(CC) $(CFLAGS) -o $(BIN)/ex1 $(SRC)/ex1.c

ex2: folders
	$(CC) $(CFLAGS) -o $(BIN)/ex2 $(SRC)/ex2.c

ex3: folders
	$(CC) $(CFLAGS) -o $(BIN)/ex3 $(SRC)/ex3.c

ex4: folders
	$(CC) $(CFLAGS) -o $(BIN)/ex4 $(SRC)/ex4.c

ex5: folders
	$(CC) $(CFLAGS) -o $(BIN)/ex5 $(SRC)/ex5.c

ex6: folders
	$(CC) $(CFLAGS) -o $(BIN)/ex6 $(SRC)/ex6.c

ex7: folders
	$(CC) $(CFLAGS) -o $(BIN)/ex7 $(SRC)/ex7.c

ex8: folders
	$(CC) $(CFLAGS) -o $(BIN)/ex8 $(SRC)/ex8.c

ex9: folders
	$(CC) $(CFLAGS) -o $(BIN)/ex9 $(SRC)/ex9.c

ex10: folders
	$(CC) $(CFLAGS) -o $(BIN)/ex10 $(SRC)/ex10.c

ex11: folders
	$(CC) $(CFLAGS) -o $(BIN)/ex11 $(SRC)/ex11.c

ex12: folders
	$(CC) $(CFLAGS) -o $(BIN)/ex12 $(SRC)/ex12.c

ex13: folders
	$(CC) $(CFLAGS) -o $(BIN)/ex13 $(SRC)/ex13.c

ex14: folders
	$(CC) $(CFLAGS) -o $(BIN)/ex14 $(SRC)/ex14.c

ex15: folders
	$(CC) $(CFLAGS) -o $(BIN)/ex15 $(SRC)/ex15.c

ex16: folders
	$(CC) $(CFLAGS) -o $(BIN)/ex16 $(SRC)/ex16.c
