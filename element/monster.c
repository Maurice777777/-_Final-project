#include "monster.h"
#include "../global.h"

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
    Monster *pDerivedObj = (Monster *)malloc(sizeof(Monster));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    // load Hero images
    char monstate_string[4][10] = {"stop", "move", "atk","atk2"};
    
    for (int i = 0; i < 4; i++)
    {
        char buffer[50];
        sprintf(buffer, "assets/image/monster/monster1-%s.gif", monstate_string[i]);
        pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    }
    // load effective sound
    // ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/monster-hit.wav");
    // pDerivedObj->mons_atk_Sound = al_create_sample_instance(sample);
    // al_set_sample_instance_playmode(pDerivedObj->mons_atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    // al_attach_sample_instance_to_mixer(pDerivedObj->mons_atk_Sound, al_get_default_mixer());

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
    pDerivedObj->mons_dir = false; // true: face to right, false: face to left
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
    return pObj;
}

int num_mons=0;

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
    else if(mons->monstate == MONATK){

    }
    else if (mons->monstate == MONATK2)
    {
        if (mons->gif_status[mons->monstate]->done)
        {
            mons->monstate = MONMOVE;
            mons->mons_new_proj = false;
        }
        else if (mons->gif_status[MONATK2]->display_index == 2 && mons->mons_new_proj == false)
        {
            Elements *blt;
            if (mons->mons_dir)
            {
                blt = New_Monsbullet(Monsbullet_L,
                                     mons->x + mons->width - 100,
                                     mons->y + 10,
                                     5);
            }
            else
            {
                blt = New_Monsbullet(Monsbullet_L,
                                     mons->x - 50,
                                     mons->y + 10,
                                     -5);
            }
            _Register_elements(scene, blt);
            mons->mons_new_proj = true;
        }
    }

    if(mons->life==0){
        change_window=2;
        self->dele=true;
    }
}

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

    // Monster *mons2 = ((Monster *)(self->pDerivedObj));
    // ALLEGRO_BITMAP *frame2 = algif_get_bitmap(mons2->gif_status[mons2->monstate1], al_get_time());
    // if (frame2)
    // {
    //     al_draw_bitmap(frame, mons2->x, mons2->y, ((mons2->mons1_dir) ? 0 : ALLEGRO_FLIP_HORIZONTAL));
    //     hp_bar(mons2->x,mons2->y,mons2->full_life1,5,mons2->life1);
    // }
    // if (mons->mons_state == MONATK && mons->gif_status[mons->monstate]->display_index == 2)
    // {
    //     al_play_sample_instance(mons->mons_atk_Sound);
    // }
}
void Monster_destory(Elements *self)
{
    printf("in d\n");
    Monster *Obj = ((Monster *)(self->pDerivedObj));
    printf("c");
    //al_destroy_sample_instance(Obj->mons_atk_Sound);
    printf("c");
    for (int i = 0; i < 4; i++){
        printf("=%d\n",i);
        algif_destroy_animation(Obj->gif_status[i]);
    }
    free(Obj->hitbox);
    free(Obj);
    free(self);

    // Monster *Obj1 = ((Monster *)(self->pDerivedObj));
    // //al_destroy_sample_instance(Obj2->mons_atk_Sound);
    // for (int i = 0; i < 3; i++)
    //     algif_destroy_animation(Obj1->gif_status2[i]);
    // free(Obj1->hitbox1);
    // free(Obj1);
    // free(self);
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

// void Reverse_Monster_update_position(Elements *self,int dx,int dy)
// {
//      Monster *mons2 = ((Monster *)(self->pDerivedObj));
//     mons2->x1 += dx;
//     mons2->y1 += dy;
//     Shape *hitbox2 = mons2->hitbox1;
//     hitbox2->update_center_x(hitbox2, dx);
//     hitbox2->update_center_y(hitbox2, dy);
// }

void Monster_interact(Elements *const self , Elements *const _target)
{
    Monster *mons = (Monster *)(self->pDerivedObj);
    //Monster *mons2 = (Monster *)(self->pDerivedObj);
    Hero* target = (Hero*)(_target->pDerivedObj);  
    if( ((0<=mons->x-target->x && mons->x-target->x<10 && mons->mons_dir==false)||
         (0<=target->x-mons->x && target->x-mons->x<10 && mons->mons_dir==true)) )
    {
        mons->monstate = MONATK;

        if(mons->gif_status[MONATK]->display_index == 5&&target->state!=dodge) {
            if(mons->minus_permit){
                int minus= 10<=target->life? 10:target->life;

                target->life-= minus;
                mons->minus_permit=false;
            }
            target->state=atked;
        }
    }
    else if( ((10<=mons->x-target->x && mons->x-target->x<500 && mons->mons_dir==false)||
         (10<=target->x-mons->x && target->x-mons->x<500 && mons->mons_dir==true)) ){
        mons->monstate = MONATK2;
    }
    else if (mons->gif_status[mons->monstate]->done)
        mons->monstate = MONMOVE;

    if(target->state==atked&&mons->gif_status[MONATK]->display_index >= 7)target->state=stop;
    if(mons->gif_status[mons->monstate]->done)mons->minus_permit=true;

    // Monster *mons2 = (Monster *)(self->pDerivedObj);
    // //Monster *mons2 = (Monster *)(self->pDerivedObj);
    // Hero* target2 = (Hero*)(_target->pDerivedObj);  
    // if( ((0<=mons2->x1-target->x && mons2->x1-target2->x<10 && mons2->mons1_dir==false)||
    //      (0<=target2->x-mons->x && target2->x-mons->x1<10 && mons2->mons1_dir==true)) )
    // {
    //     mons2->monstate = MONATK;

    //     if(mons2->gif_status2[MONATK]->display_index == 5) {
    //         if(mons2->minus2_permit){
    //             int minus= 5<=target->life? 5:target->life;

    //             target2->life-= minus;
    //             mons->minus_permit=false;
    //         }
    //     }
    // }
    // else if (mons2->gif_status2[mons2->monstate]->done)
    //     mons2->monstate = MONMOVE;
    // if(mons2->gif_status2[mons2->monstate]->done)mons2->minus_permit=true;
}