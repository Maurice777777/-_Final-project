#ifndef GG_SCENE_H_INCLUDED
#define GG_SCENE_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [hi]
*/
typedef struct _GG
{
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    ALLEGRO_BITMAP *restart; // restart image
    ALLEGRO_BITMAP *background;
    int title_x, title_y;
    int target_x,target_y,target_width,target_height;//mouse click region
} gg;
Scene *New_ggscene(int label);
void gg_update(Scene *self);
void gg_draw(Scene *self);
void gg_destroy(Scene *self);

#endif
