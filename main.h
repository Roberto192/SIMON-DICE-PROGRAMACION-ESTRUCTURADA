#ifndef DEFINE_MAIN
#define DEFINE_MAIN

#define ESCENARIO_MENU 0
#define ESCENARIO_PLAY 1
#define ESCENARIO_RECORDS 2
#define ESCENARIO_CONFIG 3

#define NOMBRE_FUENTE "img\\VT323.ttf"
#define IMAGEN_FONDO "img\\fondo.png"
#define IMAGEN_BOTONES "img\\botones_menu.png"
#define IMAGEN_LOGO "img\\simon_dice.png"
#define IMAGEN_SPRITES "img\\sprites.png"

#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

typedef struct _timagen{
    ALLEGRO_BITMAP *image;
    int width;
    int height;
    int tamx;
    int tamy;
    int posx;
    int posy;
    float x;
    float y;
    float scalex;
    float scaley;
    float _angle;
}Timagen;

int cargar_allegro();

#endif // DEFINE_MAIN
