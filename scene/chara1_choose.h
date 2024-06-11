#ifndef CH1C_H_INCLUDED
#define CH1C_H_INCLUDED
#include "scene.h"
#include "../element/hero.h"
#include "../element/character.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [Menu object]
*/
typedef enum EleTypec1c
{
    Floorc1c_L,
    Teleportc1c_L,
    Characterc1c_L,
    Treec1c_L,
    Projectilec1c_L,
    Monsterc1c_L,
    Monsbulletc1c_L,
    Heroc1c_L
} EleTypec1c;

typedef struct _ch1c
{
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE *click;
    
    ALLEGRO_SAMPLE_INSTANCE *sample_instance_click;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    ALLEGRO_BITMAP *background;
    ALLEGRO_BITMAP *start; // start image
    ALLEGRO_BITMAP *back; // start image
    ALLEGRO_BITMAP *hero1info; 
    ALLEGRO_BITMAP *rselect;  
    ALLEGRO_BITMAP *target;  
    int title_x, title_y;
    int target_x,target_y,target_width,target_height;//mouse click region
    int back_x,back_y,back_width,back_height;//back pos
    int hero1info_x,hero1info_y,hero1info_width,hero1info_height;
    int hero2info_x,hero2info_y,hero2info_width,hero2info_height;
    int rselect_x,rselect_y,rselect_width,rselect_height;
} ch1c;
Scene *New_ch1c(int label);
void ch1c_update(Scene *self);
void ch1c_draw(Scene *self);
void ch1c_destroy(Scene *self);

#endif
