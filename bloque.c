#include "bloque.h"

void obtenerFomula(float *formulax, float *formulay, int n, int x, int w, int h)
{
    int i;

    for(i = 0; i < n; i++)
    {
        formulax[i] = (float) ((w/2)-((x*n)/2)+(x*i));
    }

    for(i = 0; i < n; i++)
    {
        formulay[i] = (float) ((h/2)-((x*n)/2)+(x*i));
    }
}

void play(Tbloque *bloques, int tam, float fx[], float fy[], int fTam, ALLEGRO_FONT *font, int cant, int maxCant, char caracter)
{
    ALLEGRO_BITMAP *bloque;
    int i, j, k = 0;


    bloque = bloques[k].imagenPrincipal.image;
    al_draw_filled_rectangle(fx[0]-10, fy[0]-10, fx[2]+bloques->imagenPrincipal.tamx+10, fy[2]+bloques->imagenPrincipal.tamy+10, al_map_rgb(0x6a, 0x80, 0x85));
    al_draw_rectangle(fx[0]-10, fy[0]-10, fx[2]+bloques->imagenPrincipal.tamx+10, fy[2]+bloques->imagenPrincipal.tamy+10, al_map_rgb(0x00, 0x00, 0x00), 5);
    al_draw_textf(font, al_map_rgb(0xff, 0xff, 0xff), 40, 0, 0, "Scored: %2d",cant-1);
    al_draw_textf(font, al_map_rgb(0xff, 0xff, 0xff), WIDTH - WIDTH/2.5, 0, 0, "Max scored: %2d",maxCant);
    al_draw_bitmap_region(bloque, COORD_X(2), COORD_Y(1), bloques->imagenPrincipal.tamx, bloques->imagenPrincipal.tamy, fx[1]*1.7, fy[1], 0);
    al_draw_textf(font, al_map_rgb(0xff, 0xff, 0xff), (fx[1]*1.7) + (bloques[k].imagenPrincipal.tamx/2), fy[1], ALLEGRO_ALIGN_CENTRE, "%c",caracter);

    for(i = 0; i < fTam; i++)
    {
        for(j = 0; j < fTam; j++)
        {
            bloque = bloques[k].imagenPrincipal.image;
            //al_draw_tinted_bitmap_region(bloque, al_map_rgb(i*j*255,100*j,255*i),  (140+84)*3, 140+84, 84, 84, fx[i], fy[j], 0);
            al_draw_bitmap_region(bloque, bloques[k].imagenPrincipal.x, bloques[k].imagenPrincipal.y, bloques[k].imagenPrincipal.tamx, bloques[k].imagenPrincipal.tamy, fx[j], fy[i], 0);
            al_draw_textf(font, al_map_rgb(0xff, 0xff, 0xff), fx[j] + (bloques[k].imagenPrincipal.tamx/2), fy[i], ALLEGRO_ALIGN_CENTRE, "%c",bloques[k].letra);
            //al_draw_bitmap(bloque, fx[i], fy[j], 0);
            k++;
        }
    }
}

void obtenerBloques(ALLEGRO_BITMAP *sprite, Tbloque bloques[], int tam, Tconf *conf)
{
    int i, j;
    ALLEGRO_BITMAP *spriteClone;

    spriteClone = al_clone_bitmap(sprite);
    for(i = 0; i < tam; i++)
    {
        //bloques[i].imagenPrincipal.image = al_create_sub_bitmap(spriteClone, (140+84)*3, 140+84, 84, 84);
        bloques[i].imagenPrincipal.image = al_create_sub_bitmap(spriteClone, 0, 0, (140+84)*4, (140+84)*3);
        bloques[i].imagenPrincipal.x = COORD_X(2);
        bloques[i].imagenPrincipal.y = (140+84)*1;
        bloques[i].imagenPrincipal.tamx = 84;
        bloques[i].imagenPrincipal.tamy = 84;
        bloques[i].letra = conf->ascii[i];
    }
}

bool handlePlayKeyboard(int event, Tconf *conf, char textGame[], int *i)
{

    int j;

    for(j = 0; j < MAX_BLOQUE; j++)
    {
        if(event == conf->keys[j])
        {
            textGame[*i] = conf->ascii[j];
            *i += 1;
            textGame[*i] = '\0';
            return true;
        }
    }

    return false;
}
