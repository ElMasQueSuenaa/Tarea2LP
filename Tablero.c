#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "Cartas.h"
#include "Tablero.h"

void ***tablero;
int **matrizBarcos;

typedef struct {
    int tamanobarco;
    int orientacion;
} Barco;

void inicializarTablero(int tamano) {
    tablero = (void ***)malloc(tamano * sizeof(void **));
    matrizBarcos = (int **)malloc(tamano * sizeof(int *));

    if (tablero == NULL || matrizBarcos == NULL) {
        printf("Error al asignar memoria para el tablero o la matriz de barcos\n");
        exit(1);
    }

    for (int i = 0; i < tamano; i++) {
        tablero[i] = (void **)malloc(tamano * sizeof(void *));
        matrizBarcos[i] = (int *)malloc(tamano * sizeof(int));

        if (tablero[i] == NULL || matrizBarcos[i] == NULL) {
            printf("Error al asignar memoria para la fila %d\n", i);
            exit(1);
        }

        for (int j = 0; j < tamano; j++) {
            tablero[i][j] = NULL;
            matrizBarcos[i][j] = 0; 
        }
    }
}

void colocarBarcos() {
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
                    if ((orientacion == 0 && matrizBarcos[fila][columna + j] != 0) || 
                        (orientacion == 1 && matrizBarcos[fila + j][columna] != 0)) {  
                        espacioLibre = 0;
                        break;
                    }
                }

                if (espacioLibre) {
                    for (int j = 0; j < barcos[i]; j++) {
                        if (orientacion == 0) {
                            tablero[fila][columna + j] = malloc(sizeof(int)); 
                            matrizBarcos[fila][columna + j] = 1; 
                        } else {
                            tablero[fila + j][columna] = malloc(sizeof(int));
                            matrizBarcos[fila + j][columna] = 1;
                        }
                    }
                    printf("Barco de tamaño %d colocado.\n", barcos[i]);
                    colocado = 1;
                }
            }
        }
    }
}

void mostrarTablero() {
    printf("El tamaño del tablero es: %d\n", tamano);

    printf("Tablero:\n");
    for (int i = 0; i < tamano; i++) {
        for (int j = 0; j < tamano; j++) {
            if(turno == 1){
                printf("~ |");
            }
            else if (tablero[i][j] == NULL) {
                // Casilla vacía y no se ha disparado
                printf(" ~ ");  
            } else if (tablero[i][j] == (void *)1) {
                // Disparo fallido (sin barco)
                printf(" X ");  
            } else if (tablero[i][j] == (void *)2) {
                // Disparo acertado (barco alcanzado)
                printf(" O ");  
            }
            // Si lo deseas, puedes mostrar los barcos ocultos (para depuración):
            else if (matrizBarcos[i][j] == 1) {
                 printf(" B ");  // Barco no alcanzado (mostrar solo en depuración o al final del juego)
            }

        }
        printf("\n"); 
    }
    fflush(stdout);
}


void borrarTablero(int tamano){
    for (int i = 0; i < tamano; i++) {
        for (int j = 0; j < tamano; j++) {
        if (tablero[i][j] != NULL) {
            free(tablero[i][j]);
            }
        }
    }
}

int verificarBarcosRestantes(){
    for (int i = 0; i < tamano; i++){
        for (int j = 0; j < tamano; j++){
            if (matrizBarcos[i][j] == 1){
                printf("Quedan barcos en el tablero.\n");
                return 1;
            }
        }
    }
    return 0;
}