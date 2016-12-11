CC=g++
SRC=$(wildcard src/*.cpp)
DEP=$(wildcard include/*.h)
INC=-I./include
# LFLAGS=-lm -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
LFLAGS=-lm -lSDL2 -lSDL2_image -g
CFLAGS=--std=c++14
EXEC=hori

$(EXEC): $(SRC) $(DEP)
	$(CC) -o $@ $(SRC) $(INC) $(CFLAGS) $(LFLAGS)

.PHONY: clean

clean:
	rm $(EXEC)
