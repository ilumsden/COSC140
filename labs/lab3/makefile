
CC = g++
CFLAGS = -g
BIN = Prime1 Prime2 Prime3 Prime4

all: $(BIN)

.cpp: 
	$(CC) $(CFLAGS) -o $* $< 

.cpp.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(BIN)
