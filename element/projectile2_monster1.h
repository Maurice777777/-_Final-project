#ifndef Projectile2_H_INCLUDED
#define Projectile2_H_INCLUDED
#include "element.h"
#include "../scene/gamescene2.h" // for element label
#include "../shapes/Shape.h"
/*
   [Projectile object]
*/
typedef struct _Projectile2_monster1
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    int v;             // the velocity of projectile
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} Projectile2_monster1;
Elements *New_Projectile2_monster1(int label, int x, int y, int v);
void Projectile2_monster1_update(Elements *const ele);
void Projectile2_monster1_interact(Elements *const, Elements *const);
void Projectile2_monster1_draw(Elements *const ele);
void Projectile2_monster1_destory(Elements *const ele);
void _Projectile2_monster1_update_position(Elements *const self, int dx, int dy);
#endif
