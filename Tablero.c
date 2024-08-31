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
    for
}