CC = g++
CFLAGS = -O3 -Wall -Wextra -W -pedantic -pipe -ffast-math -fforce-addr -march=native -fomit-frame-pointer -finline-functions -funroll-loops -funsafe-loop-optimizations 

LDFLAGS =

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

ifdef DEBUG
	CFLAGS += -g
endif

EXEC=dungeon

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) 

main.o: config.h

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean :
	rm -f *.o $(EXEC)

re :
	make clean && make