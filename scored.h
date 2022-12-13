#include "main.h"
#include "configuracion.h"

typedef struct _tScored{

    char name[MAX];
    Tconf conf;
    int scored;

}Tscored;

Tscored getDefaultScored(char name[]);
Tscored getScored(char name[]);
void saveScored(Tscored *scored, int nscored);
void printScoreds(Tscored *scoreds, ALLEGRO_FONT *font);
char getRamdonAsciiChar(Tscored *scored);
void loadScoreds(bool *load_scoreds, Tscored scoreds[]);
