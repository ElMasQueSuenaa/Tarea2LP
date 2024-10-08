#ifndef H_CARTAS
#define H_CARTAS

typedef struct Mano
{
    void ** carta;
    int disponibles;
} Mano;

extern void ***tablero;
extern int tamano;
extern int turno;
extern Mano Cartas;
void inicializarMazo();
void mostrarMazo();
void usarCarta();
void borrarMazo();

void * disparoSimple(int x, int y);
void * disparoGrande(int x, int y);
void * disparoLineal(int x, int y);
void * disparoRadar(int x, int y);
void * disparo500KG(int x, int y);

#endif