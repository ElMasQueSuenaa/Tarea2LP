#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "Cartas.h"
#include "Tablero.h"

void ***tablero;
int tamano;

typedef struct {
    int tamano;
    int orientacion;
} Barco;

int barcohelp(int fila, int columna, int tamanoBarco, int orientacion, int tamanoTablero) {
    if (orientacion == 0) { 
        for (int i = 0; i < tamanoBarco; i++) {
            if (tablero[fila][columna + i] != NULL) {
                return 0; 
            }
        }
    } else {
        for (int i = 0; i < tamanoBarco; i++) {
            if (tablero[fila + i][columna] != NULL) {
                return 0;
            }
        }
    }
    return 1;
}

void inicializarTablero(int tamano) {
    tablero = (void ***)malloc(tamano * sizeof(void **));
    if (tablero == NULL) {
        printf("Error al asignar memoria para el tablero\n");
        exit(1);
    }

    for (int i = 0; i < tamano; i++) {
        tablero[i] = (void **)malloc(tamano * sizeof(void *));
        if (tablero[i] == NULL) {
            printf("Error al asignar memoria para la fila %d\n", i);
            exit(1);
        }
        for (int j = 0; j < tamano; j++) {
            tablero[i][j] = NULL;
        }
    }
    int *barcos;
    int numBarcos;

    if (tamano == 11) {
        static int barcos11[] = {2, 2, 3, 4, 5};
        barcos = barcos11;
        numBarcos = 5;
    } else if (tamano == 17) {
        static int barcos17[] = {2, 2, 2, 3, 3, 4, 5};
        barcos = barcos17;
        numBarcos = 7;
    } else if (tamano == 21) {
        static int barcos21[] = {2, 2, 2, 3, 3, 4, 4, 5, 5};
        barcos = barcos21;
        numBarcos = 9;
    }

    for (int i = 0; i < numBarcos; i++) {
        int colocado = 0;
        while (!colocado) {
            int orientacion = rand() % 2;
            int fila = rand() % tamano;
            int columna = rand() % tamano;
            if ((orientacion == 0 && columna + barcos[i] <= tamano) ||  
                (orientacion == 1 && fila + barcos[i] <= tamano)) {  
                int espacioLibre = 1;
                for (int j = 0; j < barcos[i]; j++) {
                    if ((orientacion == 0 && tablero[fila][columna + j] != NULL) ||  
                        (orientacion == 1 && tablero[fila + j][columna] != NULL)) { 
                        espacioLibre = 0;
                        break;
                    }
                }

                if (espacioLibre) {
                    for (int j = 0; j < barcos[i]; j++) {
                        if (orientacion == 0) {  
                            tablero[fila][columna + j] = malloc(sizeof(Barco));
                        } else {
                            tablero[fila + j][columna] = malloc(sizeof(Barco));
                        }
                    }
                    colocado = 1; 
                }
            }
        }
    }
}

void mostrarTablero(int tamano) {
    printf("Tablero:\n");
    for (int i = 0; i < tamano; i++) {
        for (int j = 0; j < tamano; j++) {
            if (tablero[i][j] == NULL) {
                printf(" ~ ");
            } else {
                printf(" B ");
            }
            if (j < tamano - 1) {
                printf("|");
            }
        }
        printf("\n");
        if (i < tamano - 1) {
            for (int k = 0; k < tamano; k++) {
                printf("----");
            }
            printf("\n");
        }
    }
}

void borrarTablero(int tamano){
    for (int i = 0; i < tamanoTablero; i++) {
    for (int j = 0; j < tamanoTablero; j++) {
        if (tablero[i][j] != NULL) {
            free(tablero[i][j]);
        }
    }
    free(tablero[i]);
}
free(tablero); 
}