#ifndef H_TABLERO
#define H_TABLERO

extern void *** tablero;

void inicializarTablero(int tamano);
void mostrarTablero();
void borrarTablero();
void colocarBarcos(int tamano);
int barcohelp(int x, int y, int tamanoBarco, int orientacion, int tamanoTablero);
#endif
