#include "hero.h"
#include "../scene/sceneManager.h"
#include "projectile.h"
#include "../global.h"
#include "monster.h"
#include "../shapes/Rectangle.h"
#include "../algif5/src/algif.h"
#include <stdio.h>
#include <stdbool.h>

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [Hero function]
*/
Elements *New_Hero(int label)
{
    Hero *pDerivedObj = (Hero *)malloc(sizeof(Hero));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    // load Hero images
    char state_string[7][10] = {"stop", "move", "attack","atk2","dodge","in hit","die"};
    for (int i = 0; i < 7; i++)
    {
        char buffer[50];
        sprintf(buffer, "assets/image/hero/%s.gif", state_string[i]);
        //sprintf(buffer, "assets/image/chara_%s.gif", state_string[i]);
        pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    }

    //沒動
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
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);
    pDerivedObj->dir = true; // true: face to right, false: face to left
    pDerivedObj->life=pDerivedObj->full_life=100;
    
    pDerivedObj->stiff=0;
    pDerivedObj->minus_permit=true;
    pObj->inter_obj[pObj->inter_len++] = Monster_L;
    // initial the animation component
    pDerivedObj->state = STOP;
    pDerivedObj->skill = 0;
    pDerivedObj->new_proj = false;
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Draw = Hero_draw;
    pObj->Update = Hero_update;
    pObj->Interact = Hero_interact;
    pObj->Destroy = Hero_destory;
    return pObj;
}
void Hero_update(Elements *self)
{
    Hero *chara = ((Hero *)(self->pDerivedObj));
    if(chara->life==0)    chara->state=die;
    if(chara->state==atked){
        if(chara->gif_status[chara->state]->done)chara->state=stop;
        else return;
    }

    if (chara->state == stop||chara->state == dodge)
    {
        if(key_state[ALLEGRO_KEY_L]){
            chara->state = dodge;
        }
        else if (key_state[ALLEGRO_KEY_J])
        {
            chara->state = atk;
        }
        else if (key_state[ALLEGRO_KEY_A])
        {
            chara->dir = false;
            chara->state = move;
        }
        else if (key_state[ALLEGRO_KEY_D])
        {
            chara->dir = true;
            chara->state = move;
        }
        else if (key_state[ALLEGRO_KEY_U])
        {
            chara->state=atk2;
        }
        //else if (key_state[ALLEGRO_KEY_I])
        // {
        //     chara->state=atk;
        //     chara->skill=2;
        // }

        if(chara->state == dodge){
            if(chara->dir)_Hero_update_position(self, -5, 0);
            else _Hero_update_position(self, 5, 0);
            if (chara->gif_status[chara->state]->done&&!key_state[ALLEGRO_KEY_L])
                chara->state = stop;
        }
    }
    else if (chara->state == move)
    {
        if(key_state[ALLEGRO_KEY_L]){
            chara->state = dodge;
        }
        else if (key_state[ALLEGRO_KEY_J])
        {
            chara->state = atk;
        }
        else if (key_state[ALLEGRO_KEY_A])
        {
            chara->dir = false;
            _Hero_update_position(self, -5, 0);
            chara->state = move;
        }
        else if (key_state[ALLEGRO_KEY_D])
        {
            chara->dir = true;
            _Hero_update_position(self, 5, 0);
            chara->state = move;
        }
        else if (key_state[ALLEGRO_KEY_U])
        {
            chara->state=atk;
        }
        //else if (key_state[ALLEGRO_KEY_I])
        // {
        //     chara->state=atk;
        //     chara->skill=2;
        // }

        if (chara->state==move&&!(key_state[ALLEGRO_KEY_D]||key_state[ALLEGRO_KEY_A]))
            chara->state = stop;
    }
    else if (chara->state == atk||chara->state == atk2)
    {
        if (chara->gif_status[chara->state]->done)
        {
            chara->state = stop;
        }
        // if (chara->gif_status[atk]->display_index == 2 && chara->new_proj == false)
        // {
        //     Elements *pro;
        //     if (chara->dir)
        //     {
        //         pro = New_Projectile(Projectile_L,
        //                              chara->x + chara->width - 100,
        //                              chara->y + 10,
        //                              5);
        //     }
        //     else
        //     {
        //         pro = New_Projectile(Projectile_L,
        //                              chara->x - 50,
        //                              chara->y + 10,
        //                              -5);
        //     }
        //     _Register_elements(scene, pro);
        //     chara->new_proj = true;
        // }
    }
    else if(chara->state==die&&chara->gif_status[chara->state]->done){
        self->dele=true ;
        change_window=1;
    }
}

void Hero_draw(Elements *self)
{
    // with the state, draw corresponding image
    Hero *chara = ((Hero *)(self->pDerivedObj));
    ALLEGRO_BITMAP *frame = algif_get_bitmap(chara->gif_status[chara->state], al_get_time());
    
    if (frame)
    {
        hp_bar(50,50,chara->full_life,10,chara->life);
        if(chara->state==atk2)
            chara->x-=chara->width,chara->y-=chara->height;
        if(change_window!=1)
            al_draw_bitmap(frame, chara->x, chara->y, ((chara->dir) ? 0:ALLEGRO_FLIP_HORIZONTAL ));
        if(chara->state==atk2)
            chara->x+=chara->width,chara->y+=chara->height;
    }
    // if (chara->state == atk && chara->gif_status[chara->state]->display_index == 2)
    // {
    //     al_play_sample_instance(chara->atk_Sound);
    // }
}
void Hero_destory(Elements *self)
{
    Hero *Obj = ((Hero *)(self->pDerivedObj));
    //al_destroy_sample_instance(Obj->atk_Sound);
    for (int i = 0; i < 7; i++){
        printf("in hero %d\n",i);
        algif_destroy_animation(Obj->gif_status[i]);
    }
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

void _Hero_update_position(Elements *self, int dx, int dy)
{
    Hero *chara = ((Hero *)(self->pDerivedObj));
    chara->x += dx;
    chara->y += dy;
    Shape *hitbox = chara->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}

bool Hero_intersect(int x,bool xd,int y,int type){
    if(type==0){
        if(xd==true&&0<=y-x&&y-x<=200)return true;
        else if(xd==false&&0<=x-y&&x-y<=200)return true;
        return false;
    }
    else{
        if(abs(x-y)<=400)return true;
        return false;
    }
}

void Hero_interact(Elements *self, Elements *tar) {
    Hero *hero = (Hero *)(self->pDerivedObj);
    Monster* target = (Monster*)(tar->pDerivedObj);
    
    if( hero->state == atk && 
        hero->gif_status[atk]->display_index == 3 &&
        hero->minus_permit &&
        Hero_intersect(hero->x,hero->dir,target->x,0))
    {
        int minus= 10<=target->life? 10:target->life;

        target->life-= minus;
        hero->minus_permit=false;
    }
    if(hero->state==atk2&&
            hero->gif_status[atk]->display_index >= 3 &&
            hero->gif_status[atk]->display_index <= 8&&
            Hero_intersect(hero->x+hero->width,hero->dir,target->x,1)){
        //else if(hero->atk2_conti_minus<hero->gif_status[atk]->display_index){
            target->life-= 30<=target->life? 30:target->life;
            hero->atk2_conti_minus=hero->gif_status[atk]->display_index;
        //}
    }
    

    if(hero->gif_status[hero->state]->done) hero->minus_permit=true;
}