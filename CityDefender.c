#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Cartas.h"
#include "Tablero.h"

int tamano;
int turno = 1;
int main(int argc, char const *argv[]){
    srand(time(0));
    int turnos, barcos, dificultad, hayBarcos = 1;
    int x, y, cartaSeleccionada;
    int i = 1;

    printf("Seleccione la dificultad:\n");
    printf("1. Facil -> 11 X 11 , 5 Barcos\n");
    printf("2. Medio -> 17 X 17 , 7 Barcos\n");
    printf("3. Dificil -> 21 X 21 , 9 Barcos\n");
    printf("Ingrese un número: ");
    scanf("%d", &dificultad);
    if(dificultad == 1){
        tamano = 11;
        barcos = 5;
        turnos = 20;
    }
    else if(dificultad == 2){
        tamano = 17;
        barcos = 7;
        turnos = 30;
    }
    else if(dificultad == 3){
        tamano = 21;
        barcos = 9;
        turnos = 40;
    }
    else{
        printf("Dificultad inválida\n");
        return 0;
    }
    inicializarTablero(tamano);
    inicializarMazo();

    while(turno <= turnos){
        printf("Turno %d de %d\n",turno, turnos);
        mostrarTablero();
        mostrarMazo();
        usarCarta();
        hayBarcos = verificarBarcosRestantes();
        turno++;
    }

    printf("Se acabaron los turnos. ¡Juego terminado!\n");

    borrarTablero(tamano);
    free(Cartas.carta);

    return 0;
}