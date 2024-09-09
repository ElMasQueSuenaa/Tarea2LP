#include <stdlib.h>
#include <stdio.h>
#include "Cartas.h"
#include "Tablero.h"

int main(int argc, char const *argv[]){
    int tamano, barcos, turnos, dificultad;
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
    colocarBarcosAleatorio(tamano);

    while(i <= turnos){
        printf("Turno %d de %d\n", i, turnos);
        mostrarTablero();
        mostrarMazo();
        usarCarta();

        // Incrementa el turno
        i++;

        // Verificar si quedan barcos
        if (!verificarBarcosRestantes(tamano)) {
            printf("¡Todos los barcos han sido hundidos! ¡Has ganado!\n");
            break;
        }
    }

    // Mensaje si se acaban los turnos
    if (i > turnos) {
        printf("Se acabaron los turnos. ¡Juego terminado!\n");
    }

    // Liberar memoria al final
    liberarTablero(tamano);
    free(Cartas.carta);

    return 0;
}