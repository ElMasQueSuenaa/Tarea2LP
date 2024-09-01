#include <stdlib.h>
#include <stdio.h>
#include "Cartas.h"
#include "Tablero.h"

Mano Cartas;

void inicializarMazo(){
    Cartas.carta = (void **)malloc(5 * sizeof(void *));
    for(int i = 0; i<5; i++){
        Cartas.carta[i] = disparoSimple;
    }
    Cartas.disponibles = 5;
}

void mostrarMazo(){
    printf("Cartas disponibles: \n");
    for(int i = 0; i<Cartas.disponibles; i++){
        if(Cartas.carta[i] == disparoSimple){
            printf("Disparo simple\n");
        }
        else if(Cartas.carta[i] == disparoGrande){
            printf("Disparo grande\n");
        }
        else if(Cartas.carta[i] == disparoLineal){
            printf("Disparo lineal\n");
        }
        else if(Cartas.carta[i] == disparoRadar){
            printf("Disparo radar\n");
        }
        else if(Cartas.carta[i] == disparo500KG){
            printf("Disparo 500KG\n");
        }
    }

}

void usarCarta(){
    int cartausar;
    int x, y;

    if(Cartas.disponibles == 0){
        printf("No hay cartas disponibles\n");
        return;
    }
    printf("Seleccione una carta: ");
    scanf("%d", &cartaSeleccionada);

    if(cartaSeleccionada < 1 || cartaSeleccionada > Cartas.disponibles){
        printf("Carta no disponible\n");
        return;
    }

    printf("Ingrese las coordenadas x y y: ");
    scanf("%d %d", &x, &y);
    
    void *(*funcionCarta)(int, int) = Cartas.carta[cartaSeleccionada-1];
    funcionCarta(x, y);
    for(int i = cartaSeleccionada-1; i<Cartas.disponibles-1; i++){
        Cartas.carta[i] = Cartas.carta[i+1];
    }
    Cartas.disponibles--;
}