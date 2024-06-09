#ifndef MONSTER_H_INCLUDED
#define MONSTER_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

#include "element.h"

#include "../shapes/Shape.h"
#include "../algif5/src/algif.h"

#include <stdbool.h>

/*
   [monster object]
*/
typedef enum MonsterType
{
    MONSTOP = 0,
    MONMOVE,
    MONATK,
    MONATK2
} MonsterType;
typedef struct _Monster
{
    int x, y;
    int width, height;              // the width and height of image
    int life,full_life;
    bool mons_dir;                       // true: face to right, false: face to left
    int monstate;                      // the state of character
    ALGIF_ANIMATION *gif_status[4]; // gif for each state. 0: stop, 1: move, 2:attack
    //ALLEGRO_SAMPLE_INSTANCE *mons_atk_Sound;
    int anime;      // counting the time of animation
    int anime_time; // indicate how long the animation
    bool mons_new_proj;
    bool minus_permit;
    Shape *hitbox; // the hitbox of object
} Monster;
Elements *New_Monster(int label);
void _Monster_update_position(Elements *self, int dx, int dy);
void Monster_update(Elements *self);
void Monster_interact(Elements *self, Elements *target);
void Monster_draw(Elements *self);
void Monster_destory(Elements *self);
//void hp_bar(int x,int y,int w,int h,int rest);
#endif