#ifndef CONFIGURACION_SIMON_DICE
#define CONFIGURACION_SIMON_DICE

#include "main.h"
#include "game.h"


typedef struct _tconf{
    unsigned char keys[10];
    unsigned char ascii[10];
}Tconf;

#include "bloque.h"

void configuracion(Tconf *conf);
Tconf getConfigDeafault();
int handleConfigKeyboardDown(int e, bool *press);

#endif // CONFIGURACION_SIMON_DICE
