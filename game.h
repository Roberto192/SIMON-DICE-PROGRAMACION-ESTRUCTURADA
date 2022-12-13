#ifndef GAME_SIMON_DICE

#include "main.h"
#include <ctype.h>

#define FPS 60
#define MAX 7
#define WIDTH 1280
#define HEIGHT 720

#define MAX_ELEMETS 100

int start_game();
char *getText(char text[], ALLEGRO_DISPLAY *display);
void clearText(char text[], char valor, int pos);
void asignarNombre(char nombre[], ALLEGRO_DISPLAY *display, void *scored, float x, float y);

#endif // GAME_SIMON_DICE
