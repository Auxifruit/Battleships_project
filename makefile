CC = gcc
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
INC = fonctions.h

all : exec

%.o : %.c $(INC)
	$(CC) -c $< -o $@

exec : $(OBJ)
	$(CC) $^ -o $@

debug:
	@echo $(SRC)
	@echo $(OBJ)

clean :
	rm -f *.o
	rm -f exec