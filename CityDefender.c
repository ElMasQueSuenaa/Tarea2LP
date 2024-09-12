#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Cartas.h"
#include "Tablero.h"

int tamano;
int turno = 1;


void mostrarGuiaCoordenadas() {
    /**
    Función: mostrarGuiaCoordenadas

    Parámetros:
    - Ninguno.

    Retorna:
    - No retorna ningún valor.
    * La función imprime en pantalla una guía que explica cómo se organizan las coordenadas en el tablero.
    * Si es que el jugador así lo desea.
    * Como comentario propio me costaba un poco ubicarme en el tablero, por lo que esta función me parece muy útil.
    *
    */
    printf("Guía de Coordenadas del Tablero:\n");
    printf("------------------------------------------------\n");
    printf("El tablero está organizado en un sistema de coordenadas.\n");
    printf("Las filas se identifican con el eje X (de arriba hacia abajo).\n");
    printf("Las columnas se identifican con el eje Y (de izquierda a derecha).\n");
    printf("------------------------------------------------\n");
    printf("Por ejemplo:\n");
    printf("  - (0, 0) es la primera fila y la primera columna (esquina superior izquierda).\n");
    printf("  - (0, Y) es la primera fila, con Y variando de 0 a %d (horizontal).\n", tamano - 1);
    printf("  - (X, 0) es la primera columna, con X variando de 0 a %d (vertical).\n", tamano - 1);
    printf("  - (X, Y) son las coordenadas generales donde X es la fila y Y es la columna.\n");
    printf("------------------------------------------------\n");
    printf("Para disparar, selecciona una fila (X) y una columna (Y).\n");
    printf("Por ejemplo, ingresar 5 7 significa disparar en la fila 5, columna 7.\n");
    printf("------------------------------------------------\n");
}

int main(int argc, char const *argv[]){
    srand(time(0));
    int turnos, dificultad, hayBarcos = 1;
    int ayuda;

    printf("Seleccione la dificultad:\n");
    printf("1. Facil -> 11 X 11 , 5 Barcos\n");
    printf("2. Medio -> 17 X 17 , 7 Barcos\n");
    printf("3. Dificil -> 21 X 21 , 9 Barcos\n");
    printf("Ingrese un número: ");
    scanf("%d", &dificultad);
    if(dificultad == 1){
        tamano = 11;
        turnos = 20;
    }
    else if(dificultad == 2){
        tamano = 17;
        turnos = 30;
    }
    else if(dificultad == 3){
        tamano = 21;
        turnos = 40;
    }
    else{
        printf("Dificultad inválida\n");
        return 0;
    }
    printf("Necesitas ayuda con ubicarte en el tablero? 1. Si 2. No\n");
    scanf("%d", &ayuda);
    if(ayuda == 1){
        mostrarGuiaCoordenadas();
    }
    inicializarTablero(tamano);
    colocarBarcos();
    inicializarMazo();
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    printf("Las coordenadas válidas para este tablero van de (0, 0) a (%d, %d).\n", tamano - 1, tamano - 1);
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    while(turno <= turnos){
        printf("Turno %d de %d\n",turno, turnos);
        mostrarTablero();
        mostrarMazo();
        usarCarta();
        hayBarcos = verificarBarcosRestantes();
        turno++;
    }
    printf("Se acabaron los turnos. ¡Juego terminado!\n");
    if(hayBarcos == 1){
        printf("Perdiste, quedaron barcos en el tablero.\n");
        mostrarTableroPerderdor();
    }
    else{
        printf("Ganaste, no quedaron barcos en el tablero.\n");
    }
    borrarTablero(tamano);
    free(Cartas.carta);
    borrarMatrizBarcos();

    return 0;
}