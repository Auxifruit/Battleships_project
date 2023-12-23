CC = gcc
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all : battleships

%.o : %.c
	$(CC) -c $< -o $@

battleships : $(OBJ)
	$(CC) $^ -o $@

debug:
	@echo $(SRC)
	@echo $(OBJ)

clean :
	rm -f *.o
	rm -f battleships
