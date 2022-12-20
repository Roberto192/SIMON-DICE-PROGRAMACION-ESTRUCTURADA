#include "main.h"
#include "game.h"

int main(int argc, char *argv[])
{

    cargar_allegro();
    start_game();

    return 0;
}

int cargar_allegro()
{

    if(!al_init())
    {
        printf("No se pudo iniciar allegro...");
        return 1;
    }


    al_init_image_addon();
    al_init_acodec_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_audio();
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();

}
