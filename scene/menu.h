#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [Menu object]
*/
typedef struct _Menu
{
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    ALLEGRO_SAMPLE *click;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance_click;
    ALLEGRO_BITMAP *background;
    ALLEGRO_BITMAP *start; // start image
    int title_x, title_y;
    int target_x,target_y,target_width,target_height;//mouse click region
} Menu;
Scene *New_Menu(int label);
void menu_update(Scene *self);
void menu_draw(Scene *self);
void menu_destroy(Scene *self);

#endif
