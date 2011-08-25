CC = g++
CFLAGS = -O3 -Wall -Wextra -W -pedantic -pipe -ffast-math -fforce-addr -march=native -fomit-frame-pointer -finline-functions -funroll-loops -funsafe-loop-optimizations -combine 

LDFLAGS =

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

ifeq ($(ARG),debug)
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
