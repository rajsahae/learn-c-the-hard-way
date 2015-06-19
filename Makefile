BIN=bin
SRC=src
OBJ=obj
CFLAGS=-Wall -g -I$(SRC)

EXAMPLES=ex1 ex2 ex3 ex4 ex5      \
	 ex6 ex7 ex8 ex9 ex10     \
	 ex11 ex12 ex13 ex14 ex15 \
	 ex16 ex17 ex18 ex20 ex23 \
	 ex24 ex25

all: $(EXAMPLES) ex19 ex19_b ex22

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

ex19_b: object game
	$(CC) $(CFLAGS) -o $(BIN)/$@ $(OBJ)/object.o $(OBJ)/game.o $(SRC)/$@.c

object: folders
	$(CC) $(CFLAGS) -c -o $(OBJ)/object.o $(SRC)/object.c

game: folders
	$(CC) $(CFLAGS) -c -o $(OBJ)/game.o $(SRC)/game.c

test: test_ex17 test_ex19

test_ex17: ex17
	test/ex17_test.sh

test_ex19: ex19
	test/ex19_test.exp

ex22: folders
	$(CC) $(CFLAGS) -c -o $(OBJ)/ex22.o $(SRC)/ex22.c
	$(CC) $(CFLAGS) -o $(BIN)/ex22_main $(OBJ)/ex22.o $(SRC)/ex22_main.c
