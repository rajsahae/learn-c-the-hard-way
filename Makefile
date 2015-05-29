BIN=bin
SRC=src
OBJ=obj
CFLAGS=-Wall -g -I$(SRC) -I$(OBJ)

EXAMPLES=ex1 ex2 ex3 ex4 ex5      \
	 ex6 ex7 ex8 ex9 ex10     \
	 ex11 ex12 ex13 ex14 ex15 \
	 ex16 ex17 ex18 ex19

all: $(EXAMPLES)

folders: 
	mkdir -p bin
	mkdir -p obj

clean:
	rm -rf bin
	rm -rf obj
	rm -rf ex*.dSYM
	rm -f db.dat

$(EXAMPLES): folders
	$(CC) $(CFLAGS) -o $(BIN)/$@ $(SRC)/$@.c

ex19: object.o

object.o: folders
	$(CC) $(CFLAGS) -c -o $(OBJ)/object.o $(SRC)/object.c

