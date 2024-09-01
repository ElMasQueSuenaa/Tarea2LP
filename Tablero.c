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