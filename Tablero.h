#ifndef H_TABLERO
#define H_TABLERO

extern int tamano;
extern int turno;
void inicializarTablero(int tamano);
void colocarBarcos();
void mostrarTablero();
int verificarBarcosRestantes();
void borrarTablero(int tamano);
int barcohelp(int x, int y, int tamanoBarco, int orientacion, int tamanoTablero);
void mostrarTableroPerderdor();
#endif
