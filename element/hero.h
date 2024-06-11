#ifndef HERO_H_INCLUDED
#define HERO_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "element.h"
#include "../shapes/Shape.h"
#include "../algif5/src/algif.h"
#include <stdbool.h>

/*
   [Hero object]
*/

typedef enum HeroType{
    stop=0,
    move,
    atk,
    atk2,
    dodge,
    atked,
    die
} HeroType;
typedef enum _Change_window{
    h_die=1,
    win
} _change_window;
typedef struct _Hero
{
    int x, y;
    int width, height;              // the width and height of image
    int life,full_life;
    bool minus_permit;
    bool minus_permit2;
    int stiff;
    
    int atk2_conti_minus;
    bool dir;                       // true: face to right, false: face to left
    int state;                      // the state of Hero
    ALGIF_ANIMATION *gif_status[7]; // gif for each state. 0: stop, 1: move, 2:attack
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    ALLEGRO_SAMPLE *dodgesound;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance_dodgesound;
    ALLEGRO_SAMPLE *mon1atk;
    ALLEGRO_SAMPLE_INSTANCE *mons_atk_Sound;
    ALLEGRO_SAMPLE *die;
    ALLEGRO_SAMPLE_INSTANCE *dies;
    int skill;
    int anime;      // counting the time of animation
    int anime_time; // indicate how long the animation
    bool new_proj;
    Shape *hitbox; // the hitbox of object
} Hero;
Elements *New_Hero(int label); 
void _Hero_update_position(Elements *self, int dx, int dy);
void Hero_update(Elements *self);
bool Hero_intersect(int x1,bool d1,int x2,int type);
void Hero_interact(Elements *self, Elements *target);
void Hero_interact2(Elements *self, Elements *tar);
void Hero_draw(Elements *self);
void Hero_destory(Elements *self);

#endif