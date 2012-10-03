CC = g++
CFLAGS = -O3 -Isrc -Wall -Wextra -W -pedantic -pipe -ffast-math -fforce-addr -march=native -fomit-frame-pointer -finline-functions -funroll-loops -funsafe-loop-optimizations 

.SUFFIXES : .o .cpp

LDFLAGS =

SRCDIR=src/
OBJDIR=obj/

SRC_BASE = $(wildcard $(SRCDIR)*/*.cpp $(SRCDIR)*.cpp)
OBJ_BASE = $(patsubst $(SRCDIR)%.cpp, $(OBJDIR)%.o, $(SRC_BASE))

ifdef DEBUG
	CFLAGS += -g
endif

EXEC=dungeon

all: $(EXEC)

$(EXEC) : $(OBJ_BASE)
	mkdir -p $(@D)
	$(CC) -o $@ $(OBJ_BASE) $(LDFLAGS) 

$(OBJDIR)%.o : $(SRCDIR)%.cpp
	mkdir -p $(@D)
	$(CC) -o $@ -c $< $(CFLAGS)

clean :
	rm -f *.o $(EXEC)

re :
	make clean && make
