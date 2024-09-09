#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "Cartas.h"
#include "Tablero.h"

void ***tablero;
extern int tamano;

void inicializarTablero(int tamano){
    tablero = (void ***)malloc(tamano * sizeof(void **));
    for(int i=0; i < tamano; i++){
        tablero[i] = (void **)malloc(tamano * sizeof(void *));
        for(int j=0; j < tamano; j++){
            tablero[i][j]=NULL;
        }
    }
}

void mostrarTablero(){
    int i, j;
    for(i = 0; tablero[i] != NULL; i++){
        for(j = 0; tablero[i][j] != NULL; j++){
            if(tablero[i][j] == NULL){
                printf(" |");
            }
            else if(tablero[i][j] == ((void *)1)){ 
                printf(" X|");
            }
            else if(tablero[i][j] == ((void *)2)){
                printf(" O|");
            }
        }
        printf("\n");
    }
}

void borrarTablero(){
    for(int i=0; i < tamano; i++){
        free(tablero[i]);
    }
    free(tablero);
}

int barcohelp(int x, int y, int tamanoBarco, int orientacion, int tamanoTablero) {
    if (orientacion == 0) {
        if (y + tamanoBarco > tamanoTablero){
            return 0;
        }
        for (int j = 0; j < tamanoBarco; j++) {
            if (tablero[x][y + j] != NULL){
                return 0;
            }
        } 
        if (x + tamanoBarco > tamanoTablero){
            return 0;
        }
        for (int j = 0; j < tamanoBarco; j++) {
            if (tablero[x + j][y] != NULL){
                return 0;
            }
        }
    }
    return 1;
}

void colocarBarcos(int tamano) {
    srand(time(NULL));
    int *barcos;
    int numBarcos;

    if (tamano == 11) {
        static int barcos11[] = {2, 2, 3, 4, 5};
        barcos = barcos11;
        numBarcos = 5;
    }
    else if (tamano == 17) {
        static int barcos17[] = {2, 2, 2, 3, 3, 4, 5};
        barcos = barcos17;
        numBarcos = 7;
    }
    else if (tamano == 21) {
        static int barcos21[] = {2, 2, 2, 3, 3, 4, 4, 5, 5};
        barcos = barcos21;
        numBarcos = 9;
    }
    
    for (int i = 0; i < numBarcos; i++) {
        int colocado = 0;
        while (!colocado) {
            int orientacion = rand() % 2; 
            int x = rand() % tamano;
            int y = rand() % tamano;

            if (barcohelp(x, y, barcos[i], orientacion, tamano)) {
                for (int j = 0; j < barcos[i]; j++) {
                    if (orientacion == 0) { 
                        tablero[y][x + j] = (void *)3;
                    } else {
                        tablero[y + j][x] = (void *)3;
                    }
                }
                colocado = 1;
            }
        }
    }
}
