
CC = g++
CFLAGS = -g -Wall
BIN = BST1 BST2 BST3

all: $(BIN)

BST1: BST.h bst1_usage.cpp
	$(CC) $(CFLAGS) -o BST1 bst1_usage.cpp

BST2: BST.h bst2_usage.cpp
	$(CC) $(CFLAGS) -o BST2 bst2_usage.cpp

BST3: BST.h bst3_usage.cpp
	$(CC) $(CFLAGS) -o BST3 bst3_usage.cpp

.cpp: 
	$(CC) $(CFLAGS) -o $* $<

clean:
	rm -f $(BIN) *.o
