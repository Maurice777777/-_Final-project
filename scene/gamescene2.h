#ifndef GAMESCENE2_H_INCLUDED
#define GAMESCENE2_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "../element/element.h"
#include "../element/character.h"
#include "../element/floor.h"
#include "../element/teleport.h"
#include "../element/tree.h"
#include "../element/projectile.h"
#include "../element/monster1.h"
#include <allegro5/allegro_font.h>

/*
   [game scene object]
*/
typedef enum EleType2
{
    Floor2_L,
    Teleport2_L,
    Tree2_L,
    Character2_L,
    Hero2_L,
    Projectile2_L,
    Ball2_L,
    monster1_L,
    Projectile_monster1_L,
    Projectile2_monster1_L

}EleType2;
typedef struct _GameScene2
{
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
     
    ALLEGRO_BITMAP *background;

} GameScene2;
Scene *New_GameScene2(int label);
void game_scene2_update(Scene *const pGameSceneObj);
void game_scene2_draw(Scene *const pGameSceneObj);
void game_scene2_destroy(Scene *const pGameSceneObj);

#endif
