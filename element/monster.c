#include "monster.h"
#include "charater.h"

#include "../scene/sceneManager.h"
#include "../scene/gamescene.h"
#include "../shapes/Rectangle.h"
#include "../algif5/src/algif.h"

#include <stdio.h>
#include <allegro5/allegro_primitives.h>
#include<math.h>
#include <stdbool.h>
/*
   [Hero function]
*/
Elements *New_Monster(int label)//生成初始化設定
{
    printf("init\n");
    Monster *pDerivedObj = (Monster *)malloc(sizeof(Monster));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    // load Hero images
    char monstate_string[3][10] = {"stop", "move", "atk"};
    printf("Good1");
    for (int i = 0; i < 3; i++)
    {
        char buffer[50];
        sprintf(buffer, "assets/image/monster1-%s.gif", monstate_string[i]);
        pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    }
    printf("Good2");
    // load effective sound
    // ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/atk_sound.wav");
    // pDerivedObj->atk_Sound = al_create_sample_instance(sample);
    // al_set_sample_instance_playmode(pDerivedObj->atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    // al_attach_sample_instance_to_mixer(pDerivedObj->atk_Sound, al_get_default_mixer());

    // initial the geometric information of Hero
    pDerivedObj->width = pDerivedObj->gif_status[0]->width;
    pDerivedObj->height = pDerivedObj->gif_status[0]->height;
    pDerivedObj->x = 300;
    pDerivedObj->y = HEIGHT - pDerivedObj->height - 60;
    pDerivedObj->life = pDerivedObj->full_life = 50;
    pDerivedObj->minus_permit = true;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);
    pDerivedObj->mons_dir = true; // true: face to right, false: face to left
    pObj->inter_obj[pObj->inter_len++] = Hero_L;
    // initial the animation component
    pDerivedObj->monstate = MONMOVE;
    pDerivedObj->mons_new_proj = false;
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Draw = Monster_draw;
    pObj->Update = Monster_update;
    pObj->Interact = Monster_interact;
    pObj->Destroy = Monster_destory;
    printf("init\n");
    return pObj;
}

void Monster_update(Elements *self)

{
    // use the idea of finite state machine to deal with different state
    Monster *mons = ((Monster *)(self->pDerivedObj));

    //Check boundaries and change direction if necessary
    if (mons->x <= 0) 
    {
        mons->mons_dir = true; // Change direction to right
    } 
    else if (mons->x + mons->width >= 1920) 
    {
        mons->mons_dir = false; // Change direction to left
    }

    // Move the monster
    if(mons->monstate==MONMOVE){
        if (mons->mons_dir) 
        {
            _Monster_update_position(self, 5, 0); // Move to the right
        } 
        else 
        {
            _Monster_update_position(self, -5, 0); // Move to the left
        }
    }
}
// void hp_bar(int x,int y,int w,int h,int rest){
//     //al_draw_rounded_rectangle(x, y, x+w, y+h,1,1,al_map_rgb(255,0,0),2);
//     al_draw_rectangle(x, y, x+w, y+h,al_map_rgb(255,0,0),1);
//     al_draw_filled_rounded_rectangle(x, y, x+rest,y+h,1,1, al_map_rgb(255,0,0));
// }
void Monster_draw(Elements *self)
{
    // with the state, draw corresponding image
    Monster *mons = ((Monster *)(self->pDerivedObj));
    ALLEGRO_BITMAP *frame = algif_get_bitmap(mons->gif_status[mons->monstate], al_get_time());
    if (frame)
    {
        al_draw_bitmap(frame, mons->x, mons->y, ((mons->mons_dir) ? 0 : ALLEGRO_FLIP_HORIZONTAL));
        hp_bar(mons->x,mons->y,mons->full_life,5,mons->life);
    }
    // if (mons->mons_state == MONATK && mons->gif_status[mons->monstate]->display_index == 2)
    // {
    //     al_play_sample_instance(mons->mons_atk_Sound);
    // }
}
void Monster_destory(Elements *self)
{
    Monster *Obj = ((Monster *)(self->pDerivedObj));
    al_destroy_sample_instance(Obj->mons_atk_Sound);
    for (int i = 0; i < 3; i++)
        algif_destroy_animation(Obj->gif_status[i]);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

void _Monster_update_position(Elements *self, int dx, int dy)
{
    Monster *mons = ((Monster *)(self->pDerivedObj));
    mons->x += dx;
    mons->y += dy;
    Shape *hitbox = mons->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}

void Monster_interact(Elements *const self , Elements *const _target)
{
    Monster *mons = (Monster *)(self->pDerivedObj);
    Hero* target = (Hero*)(_target->pDerivedObj);
    
    if( ((0<=mons->x-target->x && mons->x-target->x<10 && mons->mons_dir==false)||
         (0<=target->x-mons->x && target->x-mons->x<10 && mons->mons_dir==true)) )
    {
        mons->monstate = MONATK;

        if(mons->gif_status[MONATK]->display_index == 5) {
            if(mons->minus_permit){
                int minus= 5<=target->life? 5:target->life;

                target->life-= minus;
                mons->minus_permit=false;
            }
        }
    }
    else if (mons->gif_status[mons->monstate]->done)
        mons->monstate = MONMOVE;

    if(mons->gif_status[mons->monstate]->done)mons->minus_permit=true;
}