#ifndef HERO1INFO_H_INCLUDED
#define HERO1INFO_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [hi]
*/
typedef struct h1info
{
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    ALLEGRO_SAMPLE *click;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance_click;
    ALLEGRO_BITMAP *background;
    ALLEGRO_BITMAP *back;
    int back_x,back_y,back_width,back_height;//back pos
} h1info;
Scene *hero1info_scene(int label);
void hero1info_update(Scene *self);
void hero1info_draw(Scene *self);
void hero1info_destroy(Scene *self);

#endif
