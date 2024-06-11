#ifndef WINSCENE_H_INCLUDED
#define WINSCENE_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [Menu object]
*/
typedef struct _Winscene
{
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    ALLEGRO_BITMAP *background;
    int title_x, title_y;
    int target_x,target_y,target_width,target_height;
} Winscene;

Scene *New_Winscene(int label);
void winscene_update(Scene *self);
void winscene_draw(Scene *self);
void winscene_destroy(Scene *self);

#endif
