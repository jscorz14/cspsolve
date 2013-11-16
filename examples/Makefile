CC                = g++
CFLAGS_COMMON     = -I".." -std=c++11 -Wall
CFLAGS_RELEASE    = $(CFLAGS_COMMON) -O3
CFLAGS_DEBUG      = $(CFLAGS_COMMON) -O0 -g
CFLAGS            = $(CFLAGS_RELEASE)
LDFLAGS           = 
INCLUDES          = ../cspsolve.hpp

all: sudoku eightqueens
	
sudoku: sudoku.o
	$(CC) -o $@ $@.o $(CFLAGS) $(LDFLAGS)

eightqueens: eightqueens.o
	$(CC) -o $@ $@.o $(CFLAGS) $(LDFLAGS)

%.o : %.cpp $(INCLUDES)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	@rm -f sudoku.o
	@rm -f sudoku
	@rm -f eightqueens.o
	@rm -f eightqueens
