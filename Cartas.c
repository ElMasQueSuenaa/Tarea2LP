#include <stdlib.h>
#include <stdio.h>

#include "Cartas.h"
#include "Tablero.h"


extern void ***tablero;
extern int **matrizBarcos;
extern int tamano;
Mano Cartas;

void inicializarMazo(){
    /*
    Función: inicializarMazo

    Parámetros:
    - Ninguno. La función utiliza variables globales como `Cartas` para manejar el mazo.

    Retorna:
    - No retorna ningún valor explícito.

    Descripción:
    Esta función inicializa el mazo de cartas al comienzo del juego. 
    Asigna memoria dinámica para almacenar 5 cartas, todas ellas inicialmente 
    del tipo `disparoSimple`. También actualiza el número de cartas disponibles 
    en el mazo, estableciendo un total de 5 cartas.
    */
    Cartas.carta = (void **)malloc(5 * sizeof(void *));
    for(int i = 0; i<5; i++){
        Cartas.carta[i] = disparoSimple;
    }
    Cartas.disponibles = 5;
}

void mostrarMazo(){
    /*
    Función: mostrarMazo()
    
    Parámetros:
    - Ninguno. La función utiliza variables globales como `Cartas` para manejar el mazo.

    Retorna:
    - No retorna un valor explícito.

    Descripción:
    La función inicializa el marzo de cartas de forma dinamica.
    Se solicita memoria para 5 cartas y se asigna la función disparoSimple a cada una.
    Se inicializa el contador de cartas disponibles en 5.
    *
    */
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
    /*
    Función: usarCarta

    Parámetros:
    - Ninguno. La función utiliza variables globales como `Cartas` para manejar el mazo.

    Retorna:
    - No retorna un valor explícito. 
    - Termina el turno si no hay cartas disponibles o si se elige una carta inválida.

    Descripción:
    Esta función permite al jugador usar una carta del mazo disponible. 
    Solicita al jugador que seleccione una carta, luego pide las coordenadas 
    (x, y) para aplicar el efecto de la carta (como disparo simple, grande, etc.).
    Una vez usada, la carta es removida del mazo. Si la carta usada genera 
    una nueva carta, esta se añade al mazo.
    */
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

void *disparoSimple(int x, int y) {
    /*
    Función: disparoSimple

    Parámetros:
    - x: int. Coordenada X (fila) donde se desea disparar.
    - y: int. Coordenada Y (columna) donde se desea disparar.

    Retorna:
    - Retorna un puntero a la función correspondiente al siguiente tipo de disparo (disparoSimple, disparoGrande, disparoLineal, disparoRadar).
    - Retorna NULL si las coordenadas están fuera de los límites o si ya se ha disparado en esa posición previamente.

    Descripción:
    Esta función realiza un disparo en una única coordenada `(x, y)` del tablero. Si el disparo
    acierta un barco, lo marca como un "HIT". Si no hay barco en la posición, lo marca como "MISS".
    La función también determina si ya se ha disparado en esa posición y, si es así, cancela el disparo.
    Al final, en función de una probabilidad aleatoria, la función devuelve el tipo de disparo que
    se realizará en el próximo turno.
    */
    if (x < 0 || y < 0 || x >= tamano || y >= tamano) {
        printf("Coordenadas fuera de los límites.\n");
        return NULL;
    }
    if (tablero[x][y] != NULL && (tablero[x][y] == (void *)1 || tablero[x][y] == (void *)2)) {
        printf("Ya se ha disparado aquí antes, perdiste el turno y el cañón.\n");
        return NULL;
    }
    if (matrizBarcos[x][y] == 1) {
        tablero[x][y] = (void *)2; 
        matrizBarcos[x][y] = 0;
        printf("HIT!\n");
    } else {
        tablero[x][y] = (void *)1;
        printf("MISS!\n");
    }
    int probabilidad = rand() % 100;
    if (probabilidad < 65) {
        return disparoSimple;
    } else if (probabilidad < 85) {
        return disparoGrande; 
    } else if (probabilidad < 90) {
        return disparoLineal;
    } else {
        return disparoRadar; 
    }
}

void *disparoGrande(int x, int y){
    /*
    Función: disparoGrande

    Parámetros:
    - x: int. Coordenada X (fila) donde se desea disparar.
    - y: int. Coordenada Y (columna) donde se desea disparar.

    Retorna:
    - Retorna un puntero a la función correspondiente al siguiente tipo de disparo.
    - Retorna NULL si las coordenadas están fuera de los límites del tablero.

    Descripción:
    Esta función realiza un disparo en un área de 3x3 alrededor de la coordenada `(x, y)`.
    Si alguno de los disparos acierta un barco, lo marca como "HIT" en el tablero y en la matriz 
    de barcos. Si no hay barcos en las posiciones, se marca como "MISS". La función también
    decide aleatoriamente el tipo de disparo que se ejecutará en el siguiente turno.
    */
    int temp = 0;
    if(x < 0 || y < 0 || x > tamano || y > tamano){
        printf("Coordenadas fuera de los límites.\n");
        return NULL;
    }
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (i >= 0 && j >= 0 && i < tamano && j < tamano) {
                if (tablero[i][j] == NULL) {
                    tablero[i][j] = (void *)1;
                } else if (matrizBarcos[i][j] == 1) {
                    tablero[i][j] = (void *)2;
                    matrizBarcos[i][j] = 0;
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
    /*
    Función: disparoLineal

    Parámetros:
    - x: int. Coordenada X (fila) donde se desea disparar.
    - y: int. Coordenada Y (columna) donde se desea disparar.

    Retorna:
    - Retorna un puntero a la función correspondiente al siguiente tipo de disparo.
    - Retorna NULL si las coordenadas están fuera de los límites del tablero.

    Descripción:
    Esta función realiza un disparo en línea recta, ya sea horizontalmente o verticalmente,
    afectando un área de 5 casillas (2 hacia cada lado de la coordenada `(x, y)`).
    El jugador selecciona la orientación (horizontal o vertical) antes de realizar el disparo.
    Luego, se verifica si hay barcos en esas posiciones, marcando "HIT" o "MISS".
    Finalmente, se determina el tipo de disparo que se realizará en el próximo turno,
    basado en una probabilidad aleatoria.
    */
    int temp = 0;
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
    if (orientacion == 0) {
        for (int i = y - 2; i <= y + 2; i++) {
            if (i >= 0 && i < tamano) {
                if (tablero[x][i] == NULL) {
                    tablero[x][i] = (void *)1;
                } else if (matrizBarcos[x][i] == 1) {
                    tablero[x][i] = (void *)2;
                    matrizBarcos[x][i] = 0;
                    printf("HIT! en (%d, %d)\n", x, i);
                }
            }
        }
    }
    else {
        for (int i = x - 2; i <= x + 2; i++) {
            if (i >= 0 && i < tamano) {
                if (tablero[i][y] == NULL) {
                    tablero[i][y] = (void *)1;
                } else if (matrizBarcos[i][y] == 1) {
                    tablero[i][y] = (void *)2;
                    matrizBarcos[i][y] = 0;
                    printf("HIT! en (%d, %d)\n", i, y);
                }
            }
        }
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
    /*
    Función: disparoRadar

    Parámetros:
    - x: int. Coordenada X (fila) donde se desea realizar el escaneo.
    - y: int. Coordenada Y (columna) donde se desea realizar el escaneo.

    Retorna:
    - Retorna un puntero a la función correspondiente al siguiente tipo de disparo.
    - Retorna NULL si las coordenadas están fuera de los límites del tablero.

    Descripción:
    Esta función simula el comportamiento de un radar, escaneando un área de 5x5 alrededor 
    de la coordenada `(x, y)` (incluyendo la coordenada central). El radar no dispara, 
    solo detecta si hay barcos en las cercanías. Si encuentra al menos un barco, imprime 
    un mensaje de éxito. Finalmente, la función retorna el tipo de disparo que se usará 
    en el próximo turno, basado en una probabilidad aleatoria.
    */
    int temp = 0; 
    if(x < 0 || y < 0 || x > tamano || y > tamano){
        printf("Coordenadas fuera de los límites.\n");
        return NULL;
    }

    for (int i = x - 2; i <= x + 2; i++) {
        for (int j = y - 2; j <= y + 2; j++) {
            if (i >= 0 && j >= 0 && i < tamano && j < tamano) {
                if (matrizBarcos[i][j] == 1) {
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
    /*
    Función: disparo500KG

    Parámetros:
    - x: int. Coordenada X (fila) donde se desea realizar el disparo.
    - y: int. Coordenada Y (columna) donde se desea realizar el disparo.

    Retorna:
    - No retorna ningún tipo de disparo (disparo único, no genera más disparos).
    - Retorna NULL si las coordenadas están fuera de los límites del tablero.

    Descripción:
    Esta función simula el disparo de una bomba de 500KG que impacta un área grande de 11x11 
    alrededor de las coordenadas `(x, y)`. Afecta un rango de 5 casillas hacia todas las direcciones 
    desde las coordenadas centrales, verificando si hay barcos en esas posiciones. Si encuentra barcos, 
    los marca como "HIT" y actualiza tanto el tablero como la matriz de barcos.
    */
    if(x < 0 || y < 0 || x > tamano || y > tamano){
        printf("Coordenadas fuera de los límites.\n");
        return NULL;
    }
    for (int i = x - 5; i <= x + 5; i++) {
        for (int j = y - 5; j <= y + 5; j++) {
            if (i >= 0 && j >= 0 && i < tamano && j < tamano) {
                if (tablero[i][j] == NULL) {
                    tablero[i][j] = (void *)1;
                } else if (matrizBarcos[i][j] == 1) {
                    tablero[i][j] = (void *)2;
                    matrizBarcos[i][j] = 0;
                    printf("HIT! en (%d, %d)\n", i, j);
                }
            }
        }
    }
    return NULL;
}

void borrarMazo() {
    /*
    Función: borrarMazo

    Parámetros:
    - Ninguno. Utiliza la variable global `Cartas`.

    Retorna:
    - No retorna ningún valor.

    Descripción:
    Esta función libera la memoria asignada dinámicamente para las cartas en el mazo. 
    Libera cada puntero individualmente y luego libera el array de punteros. Finalmente, 
    se establece el puntero del array a NULL y se ajusta el número de cartas disponibles a 0.
    */
    
    if (Cartas.carta != NULL) {
        for (int i = 0; i < Cartas.disponibles; i++) {
            if (Cartas.carta[i] != NULL) {
                free(Cartas.carta[i]);  // Libera cada carta individual
                Cartas.carta[i] = NULL; // Evita que el puntero apunte a memoria liberada
            }
        }

        // Libera el array de punteros de las cartas
        free(Cartas.carta);
        Cartas.carta = NULL;

        // Ajustar el número de cartas disponibles a 0
        Cartas.disponibles = 0;
    }
}
