BIN=bin
SRC=src
OBJ=obj
CFLAGS=-Wall -g -I$(SRC)

EXAMPLES=ex1 ex2 ex3 ex4 ex5      \
	 ex6 ex7 ex8 ex9 ex10     \
	 ex11 ex12 ex13 ex14 ex15 \
	 ex16 ex17 ex18

all: $(EXAMPLES) ex19

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

ex19: object game
	$(CC) $(CFLAGS) -o $(BIN)/$@ $(OBJ)/object.o $(OBJ)/game.o $(SRC)/$@.c

object: folders
	$(CC) $(CFLAGS) -c -o $(OBJ)/object.o $(SRC)/object.c

game: folders
	$(CC) $(CFLAGS) -c -o $(OBJ)/game.o $(SRC)/game.c

test: ex17 ex19
	test/ex17_test.sh
	test/ex19_test.exp
