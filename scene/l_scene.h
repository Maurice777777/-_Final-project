#ifndef L_SCENE_H_INCLUDED
#define L_SCENE_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [hi]
*/
typedef struct LL
{
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    ALLEGRO_BITMAP *restart; // restart image
    ALLEGRO_BITMAP *background;
    int title_x, title_y;
    int target_x,target_y,target_width,target_height;//mouse click region
} ll;
Scene *New_l_scene(int label);
void ll_update(Scene *self);
void ll_draw(Scene *self);
void ll_destroy(Scene *self);

#endif
