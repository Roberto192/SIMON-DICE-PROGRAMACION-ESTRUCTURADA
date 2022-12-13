#include "scored.h"
#include "game.h"

Tscored getDefaultScored(char name[])
{

    Tscored scored;

    strcpy_s(scored.name, MAX+1, name);
    scored.conf = getConfigDeafault();
    scored.scored = 0;
    return scored;

}

Tscored getScored(char name[])
{

    Tscored scored;
    ALLEGRO_FILE *arch;

    arch = al_fopen("scoreds.smndc", "rb");
    if(!arch)
    {
        arch = al_fopen("scoreds.smndc", "wb");
        al_fclose(arch);
        return getDefaultScored(name);
    }

    while(al_fread(arch, &scored, sizeof(struct _tScored)))
    {
        if(strcmp(name, scored.name) == 0)
        {
            al_fclose(arch);
            return scored;
        }
    }

    al_fclose(arch);
    return getDefaultScored(name);
}

void saveScored(Tscored *scored, int nscored)
{

    ALLEGRO_FILE *arch;
    Tscored buff;
    scored->scored = nscored;
    arch = al_fopen("scoreds.smndc", "r+b");
    int i = 0;
    while(al_fread(arch, &buff, sizeof(struct _tScored)))
    {
        if(strcmp(buff.name, scored->name) == 0)
        {
            break;
        }
        else
        {
            i++;
        }
    }
    printf("pos -> %d\n",i);
    al_fseek(arch, sizeof(struct _tScored) * i, SEEK_SET);
    al_fwrite(arch, scored, sizeof(struct _tScored));
    al_fclose(arch);

}

void printScoreds(Tscored *scoreds, ALLEGRO_FONT *font)
{
    int i;

    al_draw_filled_rectangle(WIDTH/8, 12, WIDTH - WIDTH/8, HEIGHT-12, al_map_rgba(0x2C, 0x5D, 0x37, 0xbb));
    al_draw_textf(font, al_map_rgb(0xff, 0xff, 0xff), WIDTH/8+25+40, HEIGHT/12, 0, "POSICION| NOMBRE |ESCORE");
    for(i = 0; i < MAX-1; i++)
    {
        if(scoreds[i].name[0] != '\0')
            al_draw_textf(font, al_map_rgb(0xff, 0xff, 0xff), WIDTH/2+40 - WIDTH/4, (84)*(i+1) + HEIGHT/12, 0, " %1d  | %6s | %3d ", i + 1, scoreds[i].name, scoreds[i].scored);
    }

}

char getRamdonAsciiChar(Tscored *scored)
{

    return scored->conf.ascii[rand()%MAX_BLOQUE];

}

void loadScoreds(bool *load_scoreds, Tscored scoreds[])
{
    int i = 0, j = 0, k = 0;
    Tscored aux;

    if(!(*load_scoreds))
    {
        *load_scoreds = true;
        ALLEGRO_FILE *arch;
        arch = al_fopen("scoreds.smndc", "rb");
        while(al_fread(arch, &scoreds[i], sizeof(struct _tScored)))
        {
            i++;

            if(i > 1)
            {
                for(j = 0; j < i; j++)
                {
                    for(k = 0; k < i - 1; k++)
                    {
                        if(scoreds[k].scored < scoreds[k+1].scored)
                        {
                            aux = scoreds[k];
                            scoreds[k] = scoreds[k+1];
                            scoreds[k+1] = aux;
                        }
                    }
                }
            }
        }
        for(k = i; k < MAX; k++)
        {
            scoreds[k].name[0] = '\0';
        }
    }

}
