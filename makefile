CC=gcc
CFLAGS= -Wall -std=c11 -O3

PROJECT= covid19

OBJ_FILES= main.o make_list.o

$(PROJECT): $(OBJ_FILES)
	gcc $(CFLAGS) -o $(PROJECT) $(OBJ_FILES) 

clean:
	rm -f *.o $(PROJECT)