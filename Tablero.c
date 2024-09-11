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
    /*
    Función: inicializarTablero

    Parámetros:
    - tamano: int. Tamaño del tablero, tanto en filas como en columnas (tablero de tamano x tamano).

    Retorna:
    - No retorna ningún valor.

    Descripción:
    Esta función inicializa tanto el tablero del juego como la matriz que indica la ubicación de los barcos. 
    Asigna memoria dinámica para ambas estructuras, asegurando que cada celda del tablero esté vacía al inicio 
    y que la matriz de barcos esté preparada para recibir barcos. Si ocurre un error durante la asignación de 
    memoria, la función detiene el programa.
    */

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
    /*
    Función: colocarBarcos

    Parámetros:
    - Ninguno. La función utiliza la variable global `tamano` para determinar el tamaño del tablero.

    Retorna:
    - No retorna ningún valor.

    Descripción:
    Esta función coloca los barcos en el tablero de forma aleatoria. Dependiendo del tamaño del tablero 
    (`tamano`), se selecciona un conjunto predefinido de barcos con diferentes longitudes. Los barcos se colocan 
    horizontal o verticalmente en posiciones válidas del tablero, evitando la superposición de barcos.
    La matriz `matrizBarcos` se actualiza para indicar la ubicación de los barcos.
    */
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
                    colocado = 1;
                }
            }
        }
    }
}

void mostrarTablero() {
    /*
    Función: mostrarTablero

    Parámetros:
    - Ninguno. La función utiliza variables globales como `tamano`, `tablero` y `matrizBarcos` 
      para mostrar el estado del tablero actual.

    Retorna:
    - No retorna ningún valor.

    Descripción:
    Esta función imprime el tablero del juego, mostrando su estado actual para cada celda. 
    Dependiendo de si es el primer turno o no, y de los valores en el tablero y la matriz de barcos, 
    muestra diferentes símbolos:
    - " ~ " para una casilla sin disparos.
    - " X " para una casilla donde se disparó, pero no había barco.
    - " O " para una casilla donde se disparó y se acertó un barco.
    */
    printf("El tamaño del tablero es: %d\n", tamano);
    printf("Tablero:\n");
    for (int i = 0; i < tamano; i++) {
        for (int j = 0; j < tamano; j++) {
            if(turno == 1){
                printf(" ~ ");
            }
            else if (tablero[i][j] == NULL) {
                printf(" ~ ");  
            } else if (tablero[i][j] == (void *)1) {
                printf(" X ");  
            } else if (tablero[i][j] == (void *)2) {
                printf(" O ");  
            }
            else if (matrizBarcos[i][j] == 1) {
              printf(" ~ ");
            }

        }
        printf("\n"); 
    }
    fflush(stdout);
}


void borrarTablero(int tamano){
    /*
    Función: borrarTablero

    Parámetros:
    - tamano: int. Tamaño del tablero, es decir, el número de filas y columnas (tablero de tamano x tamano).

    Retorna:
    - No retorna ningún valor.

    Descripción:
    Esta función se encarga de liberar la memoria asignada dinámicamente a cada celda del tablero. 
    Recorre todas las posiciones del tablero y, si una celda está ocupada (es decir, no es `NULL`), 
    libera la memoria correspondiente. Esto evita fugas de memoria al final del juego.
    */

    for (int i = 0; i < tamano; i++) {
        for (int j = 0; j < tamano; j++) {
        if (tablero[i][j] != NULL) {
            free(tablero[i][j]);
            }
        }
    }
}

int verificarBarcosRestantes(){
    /*
    Función: verificarBarcosRestantes

    Parámetros:
    - Ninguno. La función utiliza variables globales como `tamano` y `matrizBarcos` para verificar 
      si aún quedan barcos en el tablero.

    Retorna:
    - 1: Si aún quedan barcos en el tablero.
    - 0: Si no quedan barcos en el tablero.

    Descripción:
    Esta función recorre la matriz de barcos (`matrizBarcos`) para verificar si aún quedan barcos en el tablero. 
    Si encuentra alguna posición en la matriz con un barco (indicado por el valor 1), imprime un mensaje y 
    retorna 1 para indicar que todavía quedan barcos. Si no encuentra ningún barco, retorna 0, lo que significa 
    que todos los barcos han sido eliminados.
    */

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

void mostrarTableroPerderdor() {
    /*
    Función: mostrarTableroPerdedor

    Parámetros:
    - Ninguno. La función utiliza variables globales como `tamano`, `tablero`, `matrizBarcos`, y `turno` 
      para mostrar el estado final del tablero después de perder el juego.

    Retorna:
    - No retorna ningún valor.

    Descripción:
    Esta función imprime el estado final del tablero una vez que el jugador ha perdido el juego. 
    Muestra todas las posiciones de los barcos, incluidos aquellos que no fueron descubiertos por el jugador.
    Dependiendo del estado de cada celda, imprime:
    - " ~ " para casillas no disparadas.
    - " X " para casillas disparadas sin barco.
    - " O " para casillas disparadas con barco (impacto).
    - " B " para casillas que contenían barcos no descubiertos por el jugador.
    */

    printf("El tamaño del tablero es: %d\n", tamano);
    printf("Tablero:\n");
    for (int i = 0; i < tamano; i++) {
        for (int j = 0; j < tamano; j++) {
            if(turno == 1){
                printf(" ~ ");
            }
            else if (tablero[i][j] == NULL) {
                printf(" ~ ");  
            } else if (tablero[i][j] == (void *)1) {
                printf(" X ");  
            } else if (tablero[i][j] == (void *)2) {
                printf(" O ");  
            }
            else if (matrizBarcos[i][j] == 1) {
              printf(" B ");
            }

        }
        printf("\n"); 
    }
    fflush(stdout);
}

void borrarMatrizBarcos() {
    /*
    Función: borrarMatrizBarcos

    Parámetros:
    - Ninguno. La función utiliza la variable global `matrizBarcos` y `tamano`.

    Retorna:
    - No retorna ningún valor.

    Descripción:
    Esta función se encarga de liberar la memoria dinámica que fue asignada previamente a la matriz de barcos 
    (`matrizBarcos`). Recorre todas las filas de la matriz, libera la memoria asignada a cada fila, y luego libera 
    la memoria de la estructura principal de la matriz. Finalmente, se establece `matrizBarcos` en `NULL` para 
    evitar accesos indebidos a memoria no válida después de liberar la matriz.
    */
    
    if (matrizBarcos != NULL) {
        for (int i = 0; i < tamano; i++) {
            free(matrizBarcos[i]);
        }
        free(matrizBarcos);
        matrizBarcos = NULL;
    }
}
