
CC = g++
CFLAGS = -g -Wall
BIN = Sudoku

all: $(BIN)

.cpp: 
	$(CC) $(CFLAGS) -o $* $< 

.cpp.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(BIN)
