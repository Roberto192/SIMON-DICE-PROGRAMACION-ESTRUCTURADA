#include "menu.h"

ObjetoMenu obtenerObjetoMenu()
{

    ObjetoMenu objeto;
    static ALLEGRO_BITMAP *logo;
    static ALLEGRO_BITMAP *botones;
    static ALLEGRO_BITMAP *play;
    static ALLEGRO_BITMAP *config;
    static ALLEGRO_BITMAP *records;

    int tamx_button = 503;
    int tamy_button = 89;

    botones = al_load_bitmap(IMAGEN_BOTONES);
    //cargo de datos del logo
    logo = al_load_bitmap(IMAGEN_LOGO);

    objeto.logo.image = logo;
    objeto.logo.height = al_get_bitmap_height(logo);
    objeto.logo.width = al_get_bitmap_width(logo);
    //objeto.logo.scale = 0;
    objeto.logo._angle = 0;
    objeto.logo.x = 0;
    objeto.logo.y = 0;
    objeto.logo.tamx = 864;
    objeto.logo.tamy = 121;

    //cargo de datos del play
    play = al_create_sub_bitmap(botones, 0, 0, tamx_button, (tamy_button*4)+(12*3));
    //8 -> 50
    //3 -> x
    objeto.play.img.image = play;
    objeto.play.img.height = al_get_bitmap_height(play);
    objeto.play.img.width = al_get_bitmap_width(play);
    objeto.play.img.tamx = tamx_button;
    objeto.play.img.tamy = tamy_button;
    objeto.play.img.scalex = tamx_button;
    objeto.play.img.scaley = tamy_button;
    objeto.play.img.x = 0;
    objeto.play.img.y = 0;
    objeto.play.img.posx = (1280/2) - (objeto.play.img.tamx/2);
    objeto.play.img.posy = 300;
    objeto.play.img._angle = 0;
    objeto.play.press = true;


    //cargo de datos del scored
    records = al_create_sub_bitmap(botones, (tamx_button+12)*2, 0, tamx_button, (tamy_button*4)+(12*3));

    objeto.records.img.image = records;
    objeto.records.img.height = al_get_bitmap_height(records);
    objeto.records.img.width = al_get_bitmap_width(records);
    objeto.records.img.tamx = tamx_button;
    objeto.records.img.tamy = tamy_button;
    objeto.records.img.scalex = tamx_button;
    objeto.records.img.scaley = tamy_button;
    objeto.records.img.x = 0;
    objeto.records.img.y = 0;
    objeto.records.img.posx = (1280/2) - (objeto.play.img.tamx/2);
    objeto.records.img.posy = 310 + tamy_button;
    objeto.records.img._angle = 0;
    objeto.records.press = false;

    //cargo de datos del config
    config = al_create_sub_bitmap(botones, tamx_button+12, 0, tamx_button, (tamy_button*4)+(12*3));

    objeto.configs.img.image = config;
    objeto.configs.img.height = al_get_bitmap_height(config);
    objeto.configs.img.width = al_get_bitmap_width(config);
    objeto.configs.img.tamx = tamx_button;
    objeto.configs.img.tamy = tamy_button;
    objeto.configs.img.scalex = tamx_button;
    objeto.configs.img.scaley = tamy_button;
    objeto.configs.img.x = 0;
    objeto.configs.img.y = 0;
    objeto.configs.img.posx = (1280/2) - (objeto.play.img.tamx/2);
    objeto.configs.img.posy = 320 + (tamy_button*2);
    objeto.configs.img._angle = 0;
    objeto.configs.press = false;

    return objeto;
}

int menu(ObjetoMenu *objeto)
{

    ALLEGRO_BITMAP *logo = objeto->logo.image;
    ALLEGRO_BITMAP *play = objeto->play.img.image;
    ALLEGRO_BITMAP *records = objeto->records.img.image;
    ALLEGRO_BITMAP *conf = objeto->configs.img.image;

    al_convert_mask_to_alpha(logo, al_map_rgb(0, 0, 0));
    //al_draw_bitmap(logo, objeto->logo.x, objeto->logo.y, 0);
    al_draw_scaled_bitmap(logo, objeto->logo.x, objeto->logo.y, objeto->logo.tamx, objeto->logo.tamy, objeto->logo.width/4, 0, objeto->logo.width/2, objeto->logo.height/4, 0);
    al_draw_scaled_bitmap(play, objeto->play.img.x, objeto->play.img.y, objeto->play.img.tamx, objeto->play.img.tamy, objeto->play.img.posx, objeto->play.img.posy, objeto->play.img.scalex, objeto->play.img.scaley, 0);
    al_draw_scaled_bitmap(records, objeto->records.img.x, objeto->records.img.y, objeto->records.img.tamx, objeto->records.img.tamy, objeto->records.img.posx, objeto->records.img.posy, objeto->records.img.scalex, objeto->records.img.scaley, 0);
    al_draw_scaled_bitmap(conf, objeto->configs.img.x, objeto->configs.img.y, objeto->configs.img.tamx, objeto->configs.img.tamy, objeto->configs.img.posx, objeto->configs.img.posy, objeto->configs.img.scalex, objeto->configs.img.scaley, 0);

    return 0;
}


int botonAnimacion(ObjetoMenu *objeto)
{

    float cont = 1.1;
    float contx = 1.05;
    float conty = 1.05;

    if(objeto->play.press)
    {
        objeto->play.img.scalex *= contx;
        objeto->play.img.scaley *= conty;
        if(objeto->play.img.scalex > objeto->play.img.tamx * cont)
        {
            objeto->play.img.scalex = objeto->play.img.tamx;
            objeto->play.img.scaley = objeto->play.img.tamy;
        }
        objeto->play.img.posx = (1280/2) - (objeto->play.img.scalex/2);
    }

    if(objeto->records.press)
    {
        objeto->records.img.scalex *= contx;
        objeto->records.img.scaley *= conty;
        if(objeto->records.img.scalex > objeto->records.img.tamx * cont)
        {
            objeto->records.img.scalex = objeto->records.img.tamx;
            objeto->records.img.scaley = objeto->records.img.tamy;
        }
        objeto->records.img.posx = (1280/2) - (objeto->records.img.scalex/2);
    }

    if(objeto->configs.press)
    {
        objeto->configs.img.scalex *= contx;
        objeto->configs.img.scaley *= conty;
        if(objeto->configs.img.scalex > objeto->configs.img.tamx * cont)
        {
            objeto->configs.img.scalex = objeto->configs.img.tamx;
            objeto->configs.img.scaley = objeto->configs.img.tamy;
        }
        objeto->configs.img.posx = (1280/2) - (objeto->configs.img.scalex/2);
    }

}

int formatearDatos(Timagen *imagen)
{
    imagen->scalex = imagen->tamx;
    imagen->scaley = imagen->tamy;
    imagen->posx = (1280/2) - (imagen->tamx/2);
}

void cambioDeBotones(int tipo, ObjetoMenu *objeto)
{

    if(tipo == ARRIBA)
    {
        if(objeto->play.press)
        {
            formatearDatos(&(objeto->play.img));
            objeto->play.press = false;
            objeto->configs.press = true;
        }
        else
        {
            if(objeto->records.press)
            {
                formatearDatos(&(objeto->records.img));
                objeto->records.press = false;
                objeto->play.press = true;
            }
            else
            {
                formatearDatos(&(objeto->configs.img));
                objeto->configs.press = false;
                objeto->records.press = true;
            }
        }
    }
    else
    {
        if(tipo == ABAJO)
        {
            if(objeto->play.press)
            {
                formatearDatos(&(objeto->play.img));
                objeto->play.press = false;
                objeto->records.press = true;
            }
            else
            {
                if(objeto->records.press)
                {
                    formatearDatos(&(objeto->records.img));
                    objeto->records.press = false;
                    objeto->configs.press = true;
                }
                else
                {
                    formatearDatos(&(objeto->configs.img));
                    objeto->configs.press = false;
                    objeto->play.press = true;
                }
            }
        }
    }
}

void handleMenuKeyboardDown(ObjetoMenu *objeto, int *escenario, int event, ALLEGRO_TIMER *timer)
{
    if(event == ALLEGRO_KEY_ENTER)
    {
        if(objeto->play.press)
        {
            *escenario = ESCENARIO_PLAY;
            al_start_timer(timer);
        }
        else if(objeto->records.press)
            *escenario = ESCENARIO_RECORDS;
        else if(objeto->configs.press)
            *escenario = ESCENARIO_CONFIG;
    }

    if(event == ALLEGRO_KEY_DOWN)
        cambioDeBotones(ABAJO, objeto);

    if(event == ALLEGRO_KEY_UP)
        cambioDeBotones(ARRIBA, objeto);

}

void logoAnimacion(ObjetoMenu *miMenu)
{

    miMenu->logo.y += miMenu->logo.tamy;

    if(miMenu->logo.y > miMenu->logo.tamy * 5)
    {
        miMenu->logo.y = 0;
    }
}
