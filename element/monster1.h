#ifndef MONSTER1_H_INCLUDED
#define MONSTER1_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "element.h"
#include "../shapes/Shape.h"
#include "../algif5/src/algif.h"

/*
   [character object]
*/
typedef enum monster1Type
{
    APPEAR1 = 0,
    MOVE1,
    ATK1,
    CONCEAL1,
    ANGRYWALK1,
    STOMP1,
    DIE1
} monster1Type;
typedef struct _monster1
{
    int x, y;
    //int level_start;          
    int width, height; // the width and height of image
    int life,full_life;
    bool dir_monster1;          // true: face to right, false: face to left
    bool minus_permit2;
    int mons2life,mons2full_life;
    int mons2state;         // the state of character
    ALGIF_ANIMATION* gif_status[7]; // gif for each state. 0: stop, 1: move, 2:attack
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    ALLEGRO_SAMPLE *stomp;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance_stomp;
    ALLEGRO_SAMPLE *conceals;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance_conceals;
    ALLEGRO_SAMPLE *dies;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance_dies;
    int anime;      // counting the time of animation
    int anime_time; // indicate how long the animation
    bool new_proj_monster1;
    Shape *hitbox; // the hitbox of object
    bool conceal_active;
    double conceal_start_time;
} monster1;
Elements *New_monster1(int label);
void _monster1_update_position(Elements *const self, int dx, int dy);
void monster1_update(Elements *const self);
void monster1_interact(Elements *const self, Elements *const target);
void monster1_draw(Elements *const self);
void monster1_destory(Elements *const self);

#endif
