CC=g++
SRC=$(wildcard src/*.cpp)
DEP=$(wildcard include/*.h)
LIB=-lm -lSDL2 -lSDL2_image
INC=-I./include
FLAGS=-Wall -Wextra --std=c++14
EXEC=hori

$(EXEC): $(SRC) $(DEP)
	$(CC) -o $@ $(SRC) $(INC) $(LIB) $(FLAGS)

.PHONY: clean

clean:
	rm $(EXEC)
