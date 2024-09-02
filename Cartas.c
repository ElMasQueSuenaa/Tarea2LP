#include <stdlib.h>
#include <stdio.h>
#include "Cartas.h"
#include "Tablero.h"

extern Mano Cartas;
extern void ***tablero;
extern int tamano;

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

void usarCarta() {
    int cartaSeleccionada;
    int x, y;
    if (Cartas.disponibles == 0) {
        printf("No hay cartas disponibles\n");
        return;
    }
    printf("Seleccione una carta (1 a %d): ", Cartas.disponibles);
    scanf("%d", &cartaSeleccionada);
    if (cartaSeleccionada < 1 || cartaSeleccionada > Cartas.disponibles) {
        printf("Carta no disponible\n");
        return;
    }
    printf("Ingrese las coordenadas x e y: ");
    scanf("%d %d", &x, &y);
    void *(*funcionCarta)(int, int) = Cartas.carta[cartaSeleccionada - 1];
    void *nuevaCarta = funcionCarta(x, y); 
    for (int i = cartaSeleccionada - 1; i < Cartas.disponibles - 1; i++) {
        Cartas.carta[i] = Cartas.carta[i + 1];
    }
    Cartas.disponibles--;
    if (nuevaCarta != NULL) {
        Cartas.carta[Cartas.disponibles] = nuevaCarta;
        Cartas.disponibles++;
    } else {
        printf("El cañón ha sido desactivado, no se añadirá nueva carta.\n");
    }
    mostrarMazo();
}

void *disparoSimple(int x, int y) {
    if (x < 0 || y < 0 || x >= tamano || y >= tamano) {
        printf("Coordenadas fuera de los límites.\n");
        return NULL;
    }

    if (tablero[x][y] == NULL) {
        tablero[x][y] = (void *)1; 
        printf("Disparo simple en (%d, %d): MISS!\n", x, y);
    } else if (tablero[x][y] == (void *)3) {
        tablero[x][y] = (void *)2;
        printf("Disparo simple en (%d, %d): HIT!\n", x, y);
    } else if (tablero[x][y] == (void *)1 || tablero[x][y] == (void *)2) {
        printf("Disparo simple en (%d, %d): Ya se ha disparado aquí antes.\n", x, y);
    }
    int probabilidad = rand() % 100;
    if(probabilidad < 65){
        return disparoSimple;
    }
    else if(probabilidad < 85){
        return disparoGrande;
    }
    else if(probabilidad < 90){
        return disparoLineal;
    }
    else{
        return disparoRadar;
    }
}