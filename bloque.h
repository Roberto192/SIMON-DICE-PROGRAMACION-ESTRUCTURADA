#ifndef BLOQUE_SIMON_DICE
#define BLOQUE_SIMON_DICE

#define MAX_BLOQUE 9
#include "main.h"

typedef struct _tbloque{
    Timagen imagenPrincipal;
    char letra;
    int status;
}Tbloque;

#include "configuracion.h"
#include <stdlib.h>
#include <math.h>

#define COORD_X(x) ((140+84)*x)
#define COORD_Y(y) ((140+84)*y)

void obtenerFomula(float *formulax, float *formulay, int n, int x, int w, int h);
void play(Tbloque *bloques, int tam, float fx[], float fy[], int fTam, ALLEGRO_FONT *font, int cant, int maxCant, char caracter);
void obtenerBloques(ALLEGRO_BITMAP *sprites, Tbloque bloques[], int tam, Tconf *conf);
bool handlePlayKeyboard(int event, Tconf *conf, char textGame[], int *i);

#endif // BLOQUE_SIMON_DICE
