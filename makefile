CC=gcc
CFLAGS= -Wall -g -std=c11 -O3

PROJECT= covid19

OBJ_FILES= main.o make_list.o file_manager.o sort.o select.o

$(PROJECT): $(OBJ_FILES)
	gcc $(CFLAGS) -o $(PROJECT) $(OBJ_FILES) 

clean:
	rm -f *.o $(PROJECT)