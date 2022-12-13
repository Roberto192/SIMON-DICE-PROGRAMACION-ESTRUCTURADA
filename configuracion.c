#include "configuracion.h"

void configuracion(Tconf *conf)
{
    int tam_text = 64;
    ALLEGRO_FONT *font = al_load_ttf_font(NOMBRE_FUENTE, tam_text, ALLEGRO_TTF_MONOCHROME);
    ALLEGRO_FONT *font2 = al_load_ttf_font(NOMBRE_FUENTE, tam_text/2.5, ALLEGRO_TTF_MONOCHROME);
    ALLEGRO_FONT *font3 = al_load_ttf_font(NOMBRE_FUENTE, 40, ALLEGRO_TTF_MONOCHROME);
    //ALLEGRO_BITMAP *block = al_load_bitmap("sprites.png");

    al_draw_text(font2, al_map_rgb(0xff, 0xff, 0xff), 0, 0, 0, "Presiona las teclas del 1 al 9");
    al_draw_text(font2, al_map_rgb(0xff, 0xff, 0xff), 0, tam_text/2.5, 0, "Para modificar las teclas del bloque");
    al_draw_text(font3, al_map_rgb(0xff, 0x00, 0x00), WIDTH/2 + WIDTH/5, 0, 0, "Presiona S para guardar");
    al_draw_filled_rectangle((WIDTH/2)-tam_text*3, 20, (WIDTH/2)+tam_text*3, HEIGHT-20, al_map_rgb(0x0e, 0x5f, 0x0e));
    //al_draw_bitmap_region(block, 1933, 590, 84, 84, 0, 0, 0);
    for(int i = 0; i < MAX_BLOQUE; i++)
    {
        al_draw_textf(font, al_map_rgb(0xff, 0xff, 0xff), (WIDTH/2), (tam_text+10)*i+30, ALLEGRO_ALIGN_CENTRE, "BLOQUE %d-> %c", i+1,conf->ascii[i]);
    }

    //al_destroy_bitmap(block);
    al_destroy_font(font);
    al_destroy_font(font2);
    al_destroy_font(font3);
}

Tconf getConfigDeafault()
{

    Tconf conf;

    conf.keys[0] = ALLEGRO_KEY_1;
    conf.keys[1] = ALLEGRO_KEY_2;
    conf.keys[2] = ALLEGRO_KEY_3;
    conf.keys[3] = ALLEGRO_KEY_4;
    conf.keys[4] = ALLEGRO_KEY_5;
    conf.keys[5] = ALLEGRO_KEY_6;
    conf.keys[6] = ALLEGRO_KEY_7;
    conf.keys[7] = ALLEGRO_KEY_8;
    conf.keys[8] = ALLEGRO_KEY_9;
    conf.keys[9] = '\0';

    conf.ascii[0] = '1';
    conf.ascii[1] = '2';
    conf.ascii[2] = '3';
    conf.ascii[3] = '4';
    conf.ascii[4] = '5';
    conf.ascii[5] = '6';
    conf.ascii[6] = '7';
    conf.ascii[7] = '8';
    conf.ascii[8] = '9';
    conf.ascii[9] = '\0';

    return conf;

}

int handleConfigKeyboardDown(int e, bool *press)
{
    *press = true;
    return e - ALLEGRO_KEY_1;
}
