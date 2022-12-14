#include "game.h"
#include "menu.h"
#include "configuracion.h"
#include "bloque.h"
#include "scored.h"

int start_game()
{

    /*
        Todas las variables que se ocuparan para el flujo del programa
    */

    srand(time(NULL));

    ALLEGRO_EVENT_QUEUE *event_queue;//Puntero a una cola de eventos;
    ALLEGRO_DISPLAY *display;//Puntero hacia una pantalla;
    ALLEGRO_TIMER *timer, *timerSecond, *timerTicks;/// Puntero a un temporizador timer -> el flujo de todo el juego
                                                    /// Puntero a un temporizador timerSecond -> el flujo de muestra de botones al usuario
                                                    /// Puntero a un temporizador timerTicks -> el flujo de los ticks por cada parpadeo
    ALLEGRO_BITMAP *sprites, *logo, *bloquesSprites, *background;//Puntero a mapa de bits
    ALLEGRO_EVENT event;//el que controlara todo evento
    ALLEGRO_FONT *font = al_load_ttf_font(NOMBRE_FUENTE, 84, ALLEGRO_TTF_MONOCHROME);
    ALLEGRO_FONT *GAME_OVER = al_load_ttf_font(NOMBRE_FUENTE, 168, ALLEGRO_TTF_MONOCHROME);
    ALLEGRO_MONITOR_INFO monitor_info;

    Tscored scored, scoreds[100];   ///|-----------------------------------------------------------------------|
    ObjetoMenu miMenu;              ///|   Tipo de datos abstractos que creamos los cuales estamos declarando  |
    Tbloque bloques[MAX_BLOQUE];    ///|-----------------------------------------------------------------------|

    float *formulax, *formulay;

    bool handleTimer = false;
    bool timer_event = false, redraw = false, press = false, load_scoreds = false;
    bool repetir = true;

    int estado = 2;
    int caracterAscii = '\0';
    int maxScored = 0;
    int errores = 0;
    int escenario = ESCENARIO_MENU;
    int n = (int) sqrt(MAX_BLOQUE);
    int i = 0, j = 0, k = 0, controlador_muestra = 0;//i es el index para textUser y j es el index para textGame
    int bloqueIndex = 0;

    char textGame[MAX_ELEMETS];
    char textUser[MAX_ELEMETS];
    char name[MAX];

    memset(name, '\0', MAX);

    al_get_monitor_info(0, &monitor_info);

    display = al_create_display(440,100);
    if(!display)
        return -1;

    event_queue = al_create_event_queue();
    if(!event_queue)
        return -2;

    timer = al_create_timer(1.0/FPS);
    timerSecond = al_create_timer(1.0/FPS);
    timerTicks = al_create_timer(1.0/FPS);
    if(!timer || !timerSecond || !timerTicks)
        return -3;

    sprites = al_load_bitmap(IMAGEN_SPRITES);
    if(!sprites)
        return -4;

    bloquesSprites = al_create_sub_bitmap(sprites, 1484, 141, 756, 533);
    logo = al_create_sub_bitmap(sprites, 1484, 810, 134, 134);
    background = al_load_bitmap(IMAGEN_FONDO);

    if(!sprites || !bloquesSprites || !background)
        return -5;

    al_set_app_name("SIMON DICE ...SUS");
    al_set_window_title(display, "SIMON-DICE");
    al_set_display_icon(display, logo);

    /***

        Se pide primero el nombre antes de poder iniciar los eventos del juego pricipal si no inicia el juego automatica mente

    ***/

    asignarNombre(name, display, &scored, monitor_info.x2/2 - WIDTH/2, monitor_info.y2/2 - HEIGHT/2);

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(timerSecond));
    al_register_event_source(event_queue, al_get_timer_event_source(timerTicks));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_start_timer(timer);


    /***

        formula->x
            y
        formula->y

        son una estructura que permite guardar la posicion de cada cuadro dibujado durante el juego
        Por lo que se almacenan en el arreglo formulax y formulay respectivamente del tipo de cuadrado

    ***/
    formulax = malloc(sizeof(float) * (n + 1));
    formulay = malloc(sizeof(float) * (n + 1));

    miMenu = obtenerObjetoMenu();
    obtenerBloques(bloquesSprites, bloques, MAX_BLOQUE, &scored.conf);
    obtenerFomula(formulax, formulay, n, 140, WIDTH, HEIGHT);

    /***

        Inicio de todo el corazon del juego este dejara de funcionar hasta que repetir sea igual a >> false <<

    ***/
    while(repetir)
    {
        al_wait_for_event(event_queue, &event);

        /// Cierra la ventana
        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            repetir = false;
            al_stop_timer(timer);
        }

        /// Manejo de evento de teclas con caracter
        if(event.type == ALLEGRO_EVENT_KEY_CHAR)
        {
            if(escenario == ESCENARIO_CONFIG)
            {
                if(!press)
                {
                    caracterAscii = event.keyboard.unichar;
                    if(k >= 1)
                    {
                        scored.conf.ascii[k - 1] = caracterAscii;
                        scored.conf.keys[k - 1] = event.keyboard.keycode;
                        bloques[k - 1].letra = caracterAscii;
                        k = 0;
                    }
                }
            }
        }

        /// Manejo de evento de teclas presionadas
        if(event.type == ALLEGRO_EVENT_KEY_DOWN)
        {

            /// Cierra el juego
            if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                repetir = false;
                al_stop_timer(timer);
            }
            else
            {
                if(escenario == ESCENARIO_MENU)
                {
                    handleMenuKeyboardDown(&miMenu, &escenario, event.keyboard.keycode, timerSecond);
                    timer_event = al_get_timer_started(timerSecond);
                    if(timer_event)
                    {
                        clearText(textGame, getRamdonAsciiChar(&scored), 0);
                    }
                }
                else
                {
                    if(escenario == ESCENARIO_PLAY)
                    {
                        if(!timer_event)
                            if(handlePlayKeyboard(event.keyboard.keycode, &scored.conf, textUser, &i))
                            {
                                if(textGame[j] != textUser[j])
                                {
                                    maxScored = strlen(textGame) - 1;
                                    if(maxScored > scored.scored)
                                    {
                                        saveScored(&scored, maxScored);
                                    }

                                    caracterAscii = '\0';
                                    memset(textGame, '\0', MAX_ELEMETS);
                                    memset(textUser, '\0', MAX_ELEMETS);
                                    clearText(textGame, getRamdonAsciiChar(&scored), 0);
                                    i = j = k = 0;
                                    al_draw_text(GAME_OVER, al_map_rgb(0xff, 0x40, 0), WIDTH/2, HEIGHT/2-84, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
                                    al_flip_display();
                                    al_rest(2);
                                    escenario = ESCENARIO_MENU;
                                }
                                else
                                {
                                    caracterAscii = textUser[j];
                                    j++;
                                }
                            }
                    }
                    else
                    {
                        if(escenario == ESCENARIO_CONFIG)
                        {
                            if(!press)
                            {
                                if(event.keyboard.keycode == ALLEGRO_KEY_S || event.keyboard.keycode == ALLEGRO_KEY_Q)
                                {
                                    caracterAscii = '\0';
                                    saveScored(&scored, scored.scored);
                                    escenario = ESCENARIO_MENU;
                                }

                                if(event.keyboard.keycode >= ALLEGRO_KEY_1)
                                {
                                    if(event.keyboard.keycode <= ALLEGRO_KEY_9)
                                    {
                                        k = handleConfigKeyboardDown(event.keyboard.keycode, &press) + 1;
                                    }
                                }

                            }
                            else
                            {
                                press = false;
                            }
                        }
                        else
                        {
                            if(escenario == ESCENARIO_RECORDS)
                            {
                                if(event.keyboard.keycode == ALLEGRO_KEY_Q)
                                {
                                    escenario = ESCENARIO_MENU;
                                    load_scoreds = false;
                                }
                            }
                        }
                    }
                }
            }
        }
        /// manejo de eventos del timer
        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            if(al_get_timer_count(timerSecond) >= FPS)
            {
                al_set_timer_count(timerSecond, 0);
                if(k == 0)
                {
                    al_unregister_event_source(event_queue, al_get_keyboard_event_source());
                }

                if(textGame[k] != '\0')
                {
                    for(bloqueIndex = 0; bloqueIndex < MAX_BLOQUE; bloqueIndex++)
                    {
                        if(textGame[k] == bloques[bloqueIndex].letra)
                        {
                            bloques[bloqueIndex].imagenPrincipal.y = COORD_Y(2);
                            bloques[bloqueIndex].status = 1;
                            al_start_timer(timerTicks);
                        }
                    }
                    k++;
                }
                else if(timer_event)
                {
                    al_stop_timer(timerSecond);
                    timer_event = false;
                    al_register_event_source(event_queue, al_get_keyboard_event_source());
                }
            }

            if(al_get_timer_count(timerTicks) >= FPS/2)
            {
                al_set_timer_count(timerTicks, 0);
                al_stop_timer(timerTicks);
                for(int a = 0; textGame[a] != '\0'; a++)
                {
                    for(bloqueIndex = 0; bloqueIndex < MAX_BLOQUE; bloqueIndex++)
                    {
                        if(bloques[bloqueIndex].letra == textGame[a])
                        {
                            if(bloques[bloqueIndex].status)
                            {
                                bloques[bloqueIndex].status = 0;
                                bloques[bloqueIndex].imagenPrincipal.y = COORD_Y(1);
                            }
                        }
                    }
                }
            }

            if(al_get_timer_count(timer) > FPS/8)
            {
                al_set_timer_count(timer, 0);
                botonAnimacion(&miMenu);
                logoAnimacion(&miMenu);
                redraw = true;
                if(escenario == ESCENARIO_PLAY)
                {

                    controlador_muestra++;
                    if(controlador_muestra > 30)
                    {
                        controlador_muestra = 0;
                        caracterAscii = '\0';
                    }
                }
            }
        }

        if(al_is_event_queue_empty(event_queue) || redraw)
        {
            if(repetir)
            {
                al_clear_to_color(al_map_rgb(0, 0, 0));
                if(errores == 0)
                {
                    al_draw_scaled_bitmap(background, 0, 0, 1600, 900, 0, 0, WIDTH, HEIGHT, 0);
                    if(escenario == ESCENARIO_MENU)
                    {
                        errores = menu(&miMenu);
                    }
                    else
                    {
                        if(escenario == ESCENARIO_PLAY)
                        {
                            play(bloques, MAX_BLOQUE, formulax, formulay, n, font, strlen(textGame), scored.scored, caracterAscii);
                            if(textGame[j] == '\0')
                            {
                                al_start_timer(timerSecond);
                                clearText(textGame, getRamdonAsciiChar(&scored), k);
                                k = j = 0;
                                timer_event = true;
                                memset(textUser, '\0', MAX_ELEMETS);
                                i = 0;
                            }


                            if(timer_event)
                            {
                                al_draw_filled_rectangle(formulax[0], formulay[0], formulax[2]+bloques->imagenPrincipal.tamx, formulay[2]+bloques->imagenPrincipal.tamy, al_map_rgba(0xaa, 0x00, 0x00, 0x01));
                            }

                        }
                        else
                        {
                            if(escenario == ESCENARIO_RECORDS)
                            {
                                loadScoreds(&load_scoreds, scoreds);
                                printScoreds(scoreds, font);

                            }
                            else
                            {
                                if(escenario == ESCENARIO_CONFIG)
                                {
                                    configuracion(&scored.conf);
                                    if(press)
                                    {
                                        al_draw_filled_rectangle(WIDTH/8, HEIGHT/2-84, WIDTH-WIDTH/8, HEIGHT/2, al_map_rgb(0,0,0));
                                        al_draw_text(font, al_map_rgb(0xff, 0xff, 0xff), WIDTH/2, HEIGHT/2-84, ALLEGRO_ALIGN_CENTRE, "Presiona cualquier tecla...");
                                    }
                                }
                            }
                        }
                    }

                    al_flip_display();
                }
            }

            redraw = false;
        }
    }

    al_destroy_bitmap(background);
    al_destroy_timer(timerSecond);
    al_destroy_timer(timerTicks);
    al_destroy_font(font);
    al_destroy_bitmap(bloquesSprites);
    al_destroy_bitmap(logo);
    al_destroy_bitmap(sprites);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);

    return 0;
}

char *getText(char text[], ALLEGRO_DISPLAY *display)
{

    ALLEGRO_EVENT event;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_TIMER *timer;
    ALLEGRO_FONT *font, *font2;

    int j = 0;
    event_queue = al_create_event_queue();
    if(!event_queue)
        return NULL;

    timer = al_create_timer(1.0/FPS);
    if(!timer)
        return NULL;

    font = al_load_font(NOMBRE_FUENTE, 26, ALLEGRO_TTF_MONOCHROME);
    font2 = al_load_font(NOMBRE_FUENTE, 40, ALLEGRO_TTF_MONOCHROME);
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    al_start_timer(timer);
    while(true)
    {
        al_wait_for_event(event_queue, &event);
        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }

        if(event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if(event.keyboard.keycode == ALLEGRO_KEY_ENTER)
                break;
        }

        if(event.type == ALLEGRO_EVENT_KEY_CHAR)
        {
            if(event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE)
            {
                if(j > 0)
                {
                    text[j-1] = '\0';
                    j--;
                }
            }
            else
            {
                if(j < MAX-1)
                {
                    if(isalpha(event.keyboard.unichar) || isalnum(event.keyboard.unichar))
                    {
                        text[j] = event.keyboard.unichar;
                        j++;
                        text[j] = '\0';
                    }
                }
                else
                {
                    text[j] = '\0';
                }
            }
        }

        if(al_event_queue_is_empty(event_queue))
        {
            al_clear_to_color(al_map_rgb(0x55,0x55,0x55));
            al_draw_text(font, al_map_rgb(0xff, 0xff, 0xff), 20, 0, 0, "Ingresa tu nombre: ");
            //al_draw_circle(4,100,10, al_map_rgb(0xff, 0xff, 0xff), 0);
            for(int i = 0; i < MAX-1; i++)
            {
                al_draw_filled_rectangle(20+((20+50)*i), 89, 20+50+((20+50)*i), 90, al_map_rgb(0xff, 0xff, 0xff));
                al_draw_textf(font2, al_map_rgb(0xff, 0xff, 0xff), 20+((20+50)*i)+25, 89-40, ALLEGRO_ALIGN_CENTRE, "%c",text[i]);
            }
            al_flip_display();
        }
    }

    return text;
}

void clearText(char text[], char valor, int pos)
{

    text[pos] = valor;
    text[pos + 1] = '\0';

}

void asignarNombre(char nombre[], ALLEGRO_DISPLAY *display, void *s, float x, float y)
{
    Tscored *scored = s;

    getText(nombre, display);
    if(nombre[0] == '\0')
    {
        strcpy_s(nombre, MAX, "PRUEBA");//Cambia el nombre
    }
    al_resize_display(display, WIDTH, HEIGHT);
    al_set_window_position(display, x, y);
    *scored = getScored(nombre);
}
