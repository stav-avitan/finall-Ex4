CFLAGS = -g -Wall
OBJ = Graph.o Node.o Edge.o Algo.h
CC = gcc

all: output functions

Graph.o: Graph.c Node.h Graph.h Edge.h Algo.h
	$(CC) -c $(CFLAGS) Graph.c

Node.o: Node.c Node.h Graph.h Edge.h
	$(CC) -c $(CFLAGS) Node.c

Edge.o: Edge.c Node.h Graph.h Edge.h
	$(CC) -c $(CFLAGS) Edge.c
    
Algo.o: Algo.c Algo.h
	$(CC) -c $(CFLAGS) Algo.c

libfunctions.so: $(OBJ)
	$(CC) -shared -fPIC -o libfunctions.so $(OBJ)

functions: libfunctions.so

main.o: main.c Node.h Graph.h Edge.h Algo.h
	$(CC) -c $(CFLAGS) main.c

output: main.o libfunctions.so
	$(CC) $(CFLAGS) -o Graph main.o ./libfunctions.so

.PHONY: all clean functions output

clean:
	rm -f *.o *.so $(OUTPUT)