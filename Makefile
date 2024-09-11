EXEC = CityDefender

SRCS = CityDefender.c Tablero.c Cartas.c

OBJS = CityDefender.o Tablero.o Cartas.o

CC = gcc

CFLAGS = -Wall -Werror

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

CityDefender.o: CityDefender.c Tablero.h Cartas.h
	$(CC) $(CFLAGS) -c CityDefender.c

Tablero.o: Tablero.c Tablero.h
	$(CC) $(CFLAGS) -c Tablero.c

Cartas.o: Cartas.c Cartas.h Tablero.h
	$(CC) $(CFLAGS) -c Cartas.c

valgrind: $(EXEC)
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC)

clean:
	rm -f $(OBJS) $(EXEC)

