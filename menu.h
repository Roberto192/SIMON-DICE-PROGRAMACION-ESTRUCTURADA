#ifndef MENU_SIMON_DICE

#include "main.h"

#define ARRIBA  1
#define ABAJO   2

typedef struct _tbutton{
    Timagen img;
    bool press;
}Tbutton;

typedef struct _objetoMenu{

    Timagen logo;
    Tbutton play;
    Tbutton records;
    Tbutton configs;

}ObjetoMenu;

ObjetoMenu obtenerObjetoMenu();
int menu(ObjetoMenu *objeto);
int botonAnimacion(ObjetoMenu *objeto);
int formatearDatos(Timagen *imagen);
void cambioDeBotones(int tipo, ObjetoMenu *objeto);
void handleMenuKeyboardDown(ObjetoMenu *objeto,  int *escenario, int event, ALLEGRO_TIMER *timer);
void logoAnimacion(ObjetoMenu *miMenu);

#endif // MENU_SIMON_DICE
