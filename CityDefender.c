#include <stdlib.h>
#include <stdio.h>
#include "Cartas.h"
#include "Tablero.h"

int main(int argc, char const *argv[]){
    int tamano, barcos, turnos, dificultad;
    int i = 1;
    printf(" 1. Facil -> 11 X 11 , 5 Barcos\n");
    printf(" 2. Medio -> 17 X 17 , 7 Barcos\n");
    printf(" 3. Dificil -> 21 X 21 , 9 Barcos\n");
    scanf("Ingrese un número:", &dificultad);

    if(dificultad == 1){
        tamano = 11;
        barcos = 5;
    }
    else if(dificultad == 2){
        tamano = 17;
        barcos = 7;
    }
    else if(dificultad == 3){
        tamano = 21;
        barcos = 9;
    }
    else{
        printf("Dificultad inválida\n");
        return 0;
    }

    inicializarTablero(tamano);
    inicializarMazo();
    colocarBarcos(tamano);

    while(i <= turnos){
        printf("Turno %d\n", i);
        mostrarTablero();
        printf("Cartas: \n");
        mostrarMazo();
        scanf("Selecciona una carta:", &carta);
        printf("Selecciona las coordenadas x e y: \n");
        scanf("X : ", &x);
        scanf("Y : ", &y);
        if(carta == "Simple"){
            disparoSimple(x, y);
        }
        else if(carta == "Grande"){
            disparoGrande(x, y);
        }
        else if(carta == "Lineal"){
            disparoLineal(x, y);
        }
        else if(carta == "Radar"){
            disparoRadar(x, y);
        }
        else if(carta == "500KG"){
            disparo500KG(x, y);
        }
        else{
            printf("Seleccionaste una carta inválida, perdiste el turno\n");
        }
    }
    


    return 0;
}
