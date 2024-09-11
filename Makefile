# Nombre del ejecutable
EXEC = CityDefender

# Archivos fuente
SRCS = CityDefender.c Tablero.c Cartas.c

# Archivos objeto generados
OBJS = CityDefender.o Tablero.o Cartas.o

# Compilador
CC = gcc

# Flags del compilador
CFLAGS = -Wall -Werror

# Regla para compilar el ejecutable
all: $(EXEC)

# Regla para compilar y enlazar el ejecutable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

# Reglas para compilar cada archivo objeto
CityDefender.o: CityDefender.c Tablero.h Cartas.h
	$(CC) $(CFLAGS) -c CityDefender.c

Tablero.o: Tablero.c Tablero.h
	$(CC) $(CFLAGS) -c Tablero.c

Cartas.o: Cartas.c Cartas.h Tablero.h
	$(CC) $(CFLAGS) -c Cartas.c

# Regla para ejecutar Valgrind
valgrind: $(EXEC)
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC)

# Limpiar archivos objeto y el ejecutable
clean:
	rm -f $(OBJS) $(EXEC)

