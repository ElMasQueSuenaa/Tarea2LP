#include <stdlib.h>
#include <stdio.h>

#include "Cartas.h"
#include "Tablero.h"


extern void ***tablero;
int tamano;
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
            printf(" Disparo simple |");
        }
        else if(Cartas.carta[i] == disparoGrande){
            printf(" Disparo grande |");
        }
        else if(Cartas.carta[i] == disparoLineal){
            printf(" Disparo lineal |");
        }
        else if(Cartas.carta[i] == disparoRadar){
            printf(" Disparo radar |");
        }
        else if(Cartas.carta[i] == disparo500KG){
            printf(" Disparo 500KG |");
        }
    }
    printf("\n");
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
    printf("Selecciona las coordenadas x e y:\n");
    printf("X: ");
    scanf("%d", &x);
    printf("Y: ");
    scanf("%d", &y);
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

int verificarBarcosRestantes(int tamano) {
    for (int i = 0; i < tamano; i++) {
        for (int j = 0; j < tamano; j++) {
            if (tablero[i][j] == (void *)3) { 
                return 1;  // Hay barcos restantes
            }
        }
    }
    return 0;  // No quedan barcos
}

void *disparoSimple(int x, int y) {
    int indicador;
    if (x < 0 || y < 0 || x >= tamano || y >= tamano) {
        printf("Coordenadas fuera de los límites.\n");
        return NULL;
    }

    if (tablero[x][y] == NULL) {
        tablero[x][y] = (void *)1; 
        printf("MISS!\n");
    } else if (tablero[x][y] == (void *)3) {
        tablero[x][y] = (void *)2;
        printf("HIT!\n");
    } else if (tablero[x][y] == (void *)1 || tablero[x][y] == (void *)2) {
        printf("Ya se ha disparado aquí antes, perdiste el turno.\n");
    }
    indicador = verificarBarcosRestantes(tamano);
    if (indicador == 0) {
        printf("TODOS LOS BARCOS DESTRUIDOS , DEFENZA EXITOSA!\n");
        return NULL;
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

void *disparoGrande(int x, int y){
    int temp = 0;
    int indicador;
    if(x < 0 || y < 0 || x > tamano || y > tamano){
        printf("Coordenadas fuera de los límites.\n");
        return NULL;
    }
    for(int i = x-1; i<=x+1; i++){
        for(int j = y-1; j<=y+1; j++){
            if(i >= 0 && j>=0 && i<=tamano && j<=tamano){
                if(tablero[i][j] == NULL){
                    tablero[i][j] = (void *)1;
                }
                else if(tablero[i][j] == (void *)3){
                    tablero[i][j] = (void *)2;
                    temp = 1;
                }
            }
        }
    }
    if(temp == 1){
        printf("HIT!\n");
    }
    else{
        printf("MISS!\n");
    }
    indicador = verificarBarcosRestantes(tamano);
    if (indicador == 0) {
        printf("TODOS LOS BARCOS DESTRUIDOS , DEFENZA EXITOSA!\n");
        return NULL;
    }
    int probabilidad = rand() % 100;
    if(probabilidad < 80){
        return disparoSimple;
    }
    else if(probabilidad < 83){
        return disparoGrande;
    }
    else if(probabilidad < 93){
        return disparoLineal;
    }
    else if(probabilidad < 98){
        return disparoRadar;
    }
    else{
        return disparo500KG;
    }
}

void *disparoLineal(int x, int y){
    int temp = 0;
    int indicador;
    int orientacion;
    if(x < 0 || y < 0 || x > tamano || y > tamano){
        printf("Coordenadas fuera de los límites.\n");
        return NULL;
    }
    while(temp != 1){
        printf("Ingrese la orientación (0 para horizontal, 1 para vertical): ");
        scanf("%d", &orientacion);
        if(orientacion == 0 || orientacion == 1){
            temp = 1;
        }
        else{
            printf("Orientación inválida\n");
        }
    }
    if(orientacion == 0){
        for(int i = y-2; i<=y+2; i++){
            if(i >= 0 && i <= tamano){
                if(tablero[x][i] == NULL){
                    tablero[x][i] = (void *)1;
                }
                else if(tablero[x][i] == (void *)3){
                    tablero[x][i] = (void *)2;
                    printf("HIT! en (%d, %d)\n", x, i);
                }
            }
        }
    }
    else{
        for(int i = x-2; i<=x+2; i++){
            if(i >= 0 && i <= tamano){
                if(tablero[i][y] == NULL){
                    tablero[i][y] = (void *)1;
                }
                else if(tablero[i][y] == (void *)3){
                    tablero[i][y] = (void *)2;
                    printf("HIT! en (%d, %d)\n", i, y);
                }
            }
        }
    }
    indicador = verificarBarcosRestantes(tamano);
    if (indicador == 0) {
        printf("TODOS LOS BARCOS DESTRUIDOS , DEFENZA EXITOSA!\n");
        return NULL;
    }
    int probabilidad = rand() % 100;
    if(probabilidad < 85){
        return disparoSimple;
    }
    else if(probabilidad < 90){
        return disparoGrande;
    }
    else if(probabilidad < 92){
        return disparoLineal;
    }
    else if(probabilidad < 98){
        return disparoRadar;
    }
    else{
        return disparo500KG;
    }
}

void* disparoRadar(int x, int y){
    int indicador;
    int temp = 0; 
    if(x < 0 || y < 0 || x > tamano || y > tamano){
        printf("Coordenadas fuera de los límites.\n");
        return NULL;
    }
    for(int i = x-2; i<x+2; i++){
        for(int j = y-2; i<y+2; j++){
            if(i >= 0 && j >= 0 && i <= tamano && j <= tamano){
                if(tablero[i][j] == (void *)3){
                    temp = 1;
                }    
            }
        }
    }
    if(temp == 1){
        printf("Barco encontrado en las cercanías\n");
    }
    else{
        printf("No se encontraron barcos en las cercanías\n");
    }
    int probabilidad = rand() % 100;
    if(probabilidad < 75){
        return disparoSimple;
    }
    else if(probabilidad < 90){
        return disparoGrande;
    }
    else if(probabilidad < 95){
        return disparoLineal;
    }
    else if(probabilidad < 97){
        return disparoRadar;
    }
    else{
        return disparo500KG;
    }
}

void* disparo500KG(int x, int y){

    int indicador;
    if(x < 0 || y < 0 || x > tamano || y > tamano){
        printf("Coordenadas fuera de los límites.\n");
        return NULL;
    }
    for(int i = x-5; i<x+5; i++){
        for(int j = y-5; j<y+5; j++){
            if(i >= 0 && j >= 0 && i <= tamano && j <= tamano){
                if(tablero[i][j] == NULL){
                    tablero[i][j] = (void *)1;
                }
                else if(tablero[i][j] == (void *)3){
                    tablero[i][j] = (void *)2;

                }
            }
        }
    }

    indicador = verificarBarcosRestantes(tamano);
    if (indicador == 0) {
        printf("TODOS LOS BARCOS DESTRUIDOS , DEFENZA EXITOSA!\n");
        return NULL;
    }
    return NULL;
}