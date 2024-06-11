#ifndef CH2C_H_INCLUDED
#define CH2C_H_INCLUDED
#include "scene.h"
#include "../element/character.h"
#include "../element/hero.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [Menu object]
*/
typedef enum EleTypec2c
{
    Floorc2c_L,
    Teleportc2c_L,
    Characterc2c_L,
    Treec2c_L,
    Projectilec2c_L,
    Monsterc2c_L,
    Monsbulletc2c_L,
    Heroc12c_L,
    Heroc22c_L
} EleTypec2c;

typedef struct _ch2c
{
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE *click;
    
    ALLEGRO_SAMPLE_INSTANCE *sample_instance_click;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    ALLEGRO_BITMAP *background;
    ALLEGRO_BITMAP *start; // start image
    ALLEGRO_BITMAP *back; // start image
    ALLEGRO_BITMAP *hero2info; 
    ALLEGRO_BITMAP *lselect;
    int title_x, title_y;
    int target_x,target_y,target_width,target_height;//mouse click region
    int back_x,back_y,back_width,back_height;//back pos
    int hero1info_x,hero1info_y,hero1info_width,hero1info_height;
    int hero2info_x,hero2info_y,hero2info_width,hero2info_height;
    int lselect_x,lselect_y,lselect_width,lselect_height;
} ch2c;
Scene *New_ch2c(int label);
void ch2c_update(Scene *self);
void ch2c_draw(Scene *self);
void ch2c_destroy(Scene *self);

#endif
