################################################################

BIN      = random
CC       = g++
CLIB     = -lm -lpthread
CFLAGS   = -Wall -pedantic -O3

SRC      = $(BIN).cpp
INC      = $(wildcard *.hpp)
OBJ      = $(SRC:.cpp=.o)

all : $(BIN)

clean :
	rm -f $(BIN) \
	rm -f $(OBJ) \
	rm -f *.o

################################################################

$(BIN) : $(OBJ)
	$(CC) $^ -o $@ $(CLIB)

%.o : %.cpp $(INC)
	$(CC) -c $< -o $@ $(CFLAGS)

################################################################