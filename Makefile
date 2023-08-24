################################################################

BIN      = main
CC       = g++
CLIB     = -lm -lpthread
CFLAGS   = -Wall -pedantic -O2

SRC      = $(wildcard src/*.cpp)
INC      = $(wildcard inc/*.hpp)
OBJ      = $(SRC:src/%.cpp=obj/%.o)

INC_PATH  = -I"inc/"
INC_PATH += -I"lib/stb/"

all : $(BIN)

clean :
	rm -f $(BIN) \
	rm -f $(OBJ)

################################################################

$(BIN) : $(OBJ)
	$(CC) $^ -o $@ $(CLIB)

obj/%.o : src/%.cpp $(INC)
	$(CC) -c $< -o $@ $(CFLAGS) $(INC_PATH)

################################################################