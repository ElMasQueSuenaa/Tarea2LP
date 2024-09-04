#include <stdlib.h>
#include <stdio.h>
#include "Cartas.h"
#include "Tablero.h"

void ***tablero;
extern int tamano;

void inicializarTablero(int tamano){
    tablero = (void ***)malloc(tamano * sizeof(void **));
    for(int i=0; i < tamano; i++){
        tablero[i] = (void **)malloc(tamano * sizeof(void *))
        for(int j=0; j < tamano; j++){
            tablero[i][j]=NULL
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
        else {
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
}

void colocarBarcos(int tamano) {
    srand(time(NULL));
    int numBarcos;
    if(tamano == 11){
        int barcos[] = {2, 2, 3, 4, 5};
        numBarcos = 5;
    }
    else if(tamano == 17){
        int barcos[] = {2, 2, 2, 3, 3, 4, 5};
        numBarcos = 7;
    }
    else if(tamano == 21){
        int barcos[] = {2, 2, 2, 3, 3, 4, 4, 5, 5};
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
                        tablero[x][y + j] = (void *)3;
                    } else {
                        tablero[x + j][y] = (void *)3;
                    }
                }
                colocado = 1;
            }
        }
    }
}