#include "../scene/sceneManager.h"
#include "../shapes/Rectangle.h"
#include "../algif5/src/algif.h"

#include "monster1.h"
#include "projectile_monster1.h"
#include "projectile2_monster1.h"


#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro_primitives.h>
#include<math.h>
#include <stdbool.h>
// #include <windows.h>
/*
   [Character function]
*/
Elements *New_monster1(int label)
{
    monster1 *pDerivedObj = (monster1 *)malloc(sizeof(monster1));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    // load character images
    pDerivedObj->mons2state = MOVE1; // this
    char state_string[7][10] = {"appear", "walk", "attack", "conceal","walk","stomp","die"};
    for (int i = 0; i < 7; i++)
    {
        char buffer[50];
        sprintf(buffer, "assets/image/monster1_%s.gif", state_string[i]);
        pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    }
    // load effective sound
    ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/mon2_punch.mp3");
    pDerivedObj->atk_Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pDerivedObj->atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->atk_Sound, al_get_default_mixer());
    al_set_sample_instance_gain(pDerivedObj->atk_Sound, 0.4);

    pDerivedObj->stomp = al_load_sample("assets/sound/mon2_stomp.mp3");
            al_reserve_samples(10);
           pDerivedObj->sample_instance_stomp = al_create_sample_instance(pDerivedObj->stomp);
            al_set_sample_instance_playmode(pDerivedObj->sample_instance_stomp, ALLEGRO_PLAYMODE_ONCE);
            al_restore_default_mixer();
            al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance_stomp, al_get_default_mixer());
            // set the volume of instance
            al_set_sample_instance_gain(pDerivedObj->sample_instance_stomp, 0.3);
    
    pDerivedObj->conceals = al_load_sample("assets/sound/mon2_conceal.mp3");
            al_reserve_samples(10);
           pDerivedObj->sample_instance_conceals = al_create_sample_instance(pDerivedObj->conceals);
            al_set_sample_instance_playmode(pDerivedObj->sample_instance_conceals, ALLEGRO_PLAYMODE_ONCE);
            al_restore_default_mixer();
            al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance_conceals, al_get_default_mixer());
            // set the volume of instance
            al_set_sample_instance_gain(pDerivedObj->sample_instance_conceals, 0.5);

    pDerivedObj->dies = al_load_sample("assets/sound/mon2_die.mp3");
            al_reserve_samples(3);
           pDerivedObj->sample_instance_dies = al_create_sample_instance(pDerivedObj->dies);
            al_set_sample_instance_playmode(pDerivedObj->sample_instance_dies, ALLEGRO_PLAYMODE_ONCE);
            al_restore_default_mixer();
            al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance_dies, al_get_default_mixer());
            // set the volume of instance
            al_set_sample_instance_gain(pDerivedObj->sample_instance_dies, 0.3);

    // initial the geometric information of character
    pDerivedObj->width = pDerivedObj->gif_status[0]->width;
    pDerivedObj->height = pDerivedObj->gif_status[0]->height - 80;
    pDerivedObj->x = 1000;
    pDerivedObj->y = HEIGHT - pDerivedObj->height - 90;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);
    pObj->inter_obj[pObj->inter_len++] = Hero2_L;
    pDerivedObj->dir_monster1 = false; // true: face to right, false: face to left
    // initial the animation component
    pDerivedObj->mons2state = STOP;
    pDerivedObj->new_proj_monster1 = false;
    pDerivedObj->minus_permit2 = true;
    pObj->pDerivedObj = pDerivedObj;
    pDerivedObj->life = pDerivedObj->full_life = 500;
    // setting derived object function
    pObj->Draw = monster1_draw;
    pObj->Update = monster1_update;
    pObj->Interact = monster1_interact;
    pObj->Destroy = monster1_destory;
    return pObj;
}

// void monster1_interact(Elements *const self_ele, Elements *const ele)
// {
//     monster1 *obj = ((monster1 *)(self_ele->pDerivedObj));
//      if (ele->label == Character_L)
//     {
//          Character *obj2 = ((Character *)(ele->pDerivedObj));
//             while((obj->x)<(obj2->x)){
//                 obj->dir_monster1 = true;
//                 _monster1_update_position(ele, 2, 0);
//             }
//         }
//     }
int levelstart = 0, atkcount=0,coolcounter=420,coolcounterdecrease=0;;

void monster1_interact(Elements *const self, Elements *const target)
{
    monster1 *self_monster = (monster1 *)(self->pDerivedObj);
    Hero *target_character = (Hero *)(target->pDerivedObj);

    

    // 獲取 Character 的 x 位置
    int target_x = target_character->x;
    // self_monster->level_start=0;

    // 根據 Character 的位置更新 monster1 的位置和方向
 if(levelstart==1)
 {
    if (self_monster->mons2state == CONCEAL1)
    {
        al_play_sample_instance(self_monster->sample_instance_conceals);
        self_monster->y = HEIGHT - self_monster->height - 80;
        if (self_monster->gif_status[self_monster->mons2state]->done)
        {
            printf("conceal animition done.");
            self_monster->mons2state = APPEAR1;
            self_monster->y = HEIGHT - self_monster->height - 120;
            self_monster->x = target_x;
            // self_monster->gif_status[CONCEAL1]->notdone;

            // self_monster->new_proj_monster1 = true;
        }
    }
    
    if (coolcounter==0)
    {
        Elements *pro2;
        pro2=New_Projectile2_monster1(Projectile2_monster1_L, target_character->x,-1,7);
        _Register_elements(scene, pro2);
        coolcounter=420-coolcounterdecrease;
        if(coolcounterdecrease<=220){
            coolcounterdecrease+=10;
        }
        // if (chara->gif_status[CONCEAL1]->done) {
        // chara->y=1000;
        // sleep(6);
        // chara->state=MOVE1;// Set state to conceal
        //}
    }

    coolcounter--;

    if(self_monster->mons2state == ANGRYWALK1){
        if ((self_monster->x < target_x - 50) && (((target_x - 50) - (self_monster->x)) > 100))
        { 
            self_monster->y = HEIGHT - self_monster->height - 70;
            self_monster->dir_monster1 = true;     // 面向右邊
            _monster1_update_position(self, 3, 0); // 向右移動
        }
        else if ((self_monster->x > target_x + 50) && (((self_monster->x) - (target_x - 50)) > 100))
        { 
            self_monster->y = HEIGHT - self_monster->height - 70;
            self_monster->dir_monster1 = false;     // 面向左邊
            _monster1_update_position(self, -3, 0); // 向左移動
        }else{
            self_monster->mons2state=STOMP1;
        }

    }

    if (self_monster->mons2state == MOVE1)
    {
        if ((self_monster->x < target_x - 50) && (((target_x - 50) - (self_monster->x)) > 600))
        { // 如果 monster1 在 Character 左邊
            // if((self_monster->state == ATK1)||(self_monster->state == CONCEAL1)){
            // if(self_monster->gif_status[self_monster->state]->done){
            self_monster->y = HEIGHT - self_monster->height - 70;
            // self_monster->state = MOVE1; // 設置狀態為 "walk",this
            self_monster->dir_monster1 = true;     // 面向右邊
            _monster1_update_position(self, 1, 0); // 向右移動
        }

        else if ((self_monster->x > target_x + 50) && (((self_monster->x) - (target_x - 50)) > 600))
        { // 如果 monster1 在 Character 右邊
            // if((self_monster->state == ATK1)||(self_monster->state == CONCEAL1)){
            // if(self_monster->gif_status[self_monster->state]->done){
            self_monster->y = HEIGHT - self_monster->height - 70;
            // self_monster->state = MOVE1; // 設置狀態為 "walk",this
            self_monster->dir_monster1 = false;     // 面向左邊
            _monster1_update_position(self, -1, 0); // 向左移動
        }

        else if ((self_monster->x < target_x - 50) && (((target_x - 50) - (self_monster->x)) <= 600))
        { // 如果 monster1 在 Character 左邊
            // self_monster->y+=20;
            // self_monster->y= height+30;
            self_monster->y = HEIGHT - self_monster->height - 10;
            self_monster->mons2state = ATK1;         // 設置狀態為 "walk",this
            self_monster->dir_monster1 = false; // 面向右邊
            //_monster1_update_position(self, 1, 0); // 向右移動
        }
        else if ((self_monster->x > target_x - 50) && (((self_monster->x) - (target_x - 50)) <= 600))
        { // 如果 monster1 在 Character 右邊
            // self_monster->y+=20;
            // self_monster->y = height+30;
            self_monster->y = HEIGHT - self_monster->height - 10;
            self_monster->mons2state = ATK1;        // 設置狀態為 "walk",this;
            self_monster->dir_monster1 = true; // 面向左邊
            //_monster1_update_position(self, -1, 0); // 向左移動
        }
    }

    if(self_monster->mons2state==STOMP1){
            al_play_sample_instance(self_monster->sample_instance_stomp);
        if(self_monster->x > target_x - 50){
            self_monster->dir_monster1 = true;
        }else{
            self_monster->dir_monster1 = false;
        }
        if(self_monster->gif_status[self_monster->mons2state]->done){
            if(target_character->life>=(target_character->full_life)/3){
            target_character->life-=(target_character->full_life)/3;
            }else{
                 target_character->life-=target_character->life;
            }
            atkcount = 0;
            self_monster->mons2state=CONCEAL1;
        }
    }
    if( target_character->state == atk && 
        target_character->gif_status[atk]->display_index == 3 &&
        self_monster->minus_permit2 &&
        Hero_intersect(target_character->x,target_character->dir,self_monster->x,0))
    {
        int minus= 100<=self_monster->life? 100:self_monster->life;

        self_monster->life-= minus;
        self_monster->minus_permit2=false;
    }
    if(self_monster->gif_status[self_monster->mons2state]->done)self_monster->minus_permit2=true;

  }
}

void monster1_update(Elements *const ele)
{
    // use the idea of finite state machine to deal with different state
    monster1 *chara = ((monster1 *)(ele->pDerivedObj));
    // Character *target = (Character *)(target->pDerivedObj);
    //ALLEGRO_TIMER *shellTimer = al_create_timer(1.0);
    //time_t starttime, endtime;
    if(chara->life==0){chara->mons2state=DIE1;}
    // int atkcount=0;
    if (levelstart == 0)
    {
        chara->mons2state = APPEAR1;
        //if (chara->gif_status[chara->mons2state]->done){
             //levelstart=1;
        //}
        // monster1_draw(chara);
        // monster1_destory(chara);
    }
    if (chara->mons2state == APPEAR1)
    {
        if (chara->gif_status[chara->mons2state]->done)
        {
            levelstart = 1;
            chara->mons2state = MOVE1;
        }
    }
    /*if (chara->state == STOP1 )
    {
        //monster1_interact(monster1, Character);
        //monster1_interact(monster1 *const monster1_L, Elements *const Character_L)
        if (key_state[ALLEGRO_KEY_SPACE])
        {
            chara->state = ATK1;
        }
        else if (key_state[ALLEGRO_KEY_N])
        {
            chara->dir_monster1 = false;
            chara->state = MOVE1;
        }
        else if (key_state[ALLEGRO_KEY_M])
        {
            chara->dir_monster1 = true;
            chara->state = MOVE1;
        }
        else
        {
            chara->state = STOP1;
        }
    }
    if (chara->state == MOVE1)
    {
        while( (Character (chara->pDerivedObj)->x) < ( monster1 (chara->pDerivedObj)->x)){
            _monster1_update_position(ele, -1, 0);

        }
    }*/
    if (levelstart == 1)
    {
        /*if (chara->state == MOVE1)
        {
            if (key_state[ALLEGRO_KEY_SPACE])
            {
                chara->state = ATK1;
            }
            else if (key_state[ALLEGRO_KEY_N])
            {
                chara->dir_monster1 = false;
                _monster1_update_position(ele, -2, 0);
                chara->state = MOVE1;
            }
            else if (key_state[ALLEGRO_KEY_M])
            {
                chara->dir_monster1 = true;
                _monster1_update_position(ele, 2, 0);
                chara->state = MOVE1;
            }
            if (chara->gif_status[chara->state]->done)
                chara->state = STOP1;
        }*/
        if (chara->mons2state == ATK1)
        {
            //atkcount+=1;
            //printf("%d\n",atkcount);
            //while(chara->mons2state == ATK1){
                //if (chara->gif_status[chara->mons2state]->done) {
                    //atkcount+=1;
                    //printf("%d\n",atkcount);
                //}

            //}
            if (chara->gif_status[chara->mons2state]->done)
            {
                // chara->state = STOP1;
                chara->mons2state = MOVE1;
                chara->new_proj_monster1 = false;
                atkcount += 1; // Increment the attack counter
                printf("atkcount is %d\n", atkcount);
            }

            if ((atkcount)&&(atkcount%6==0))
            {
                chara->mons2state = CONCEAL1;
                atkcount+=1;
                // if (chara->gif_status[CONCEAL1]->done) {
                // chara->y=1000;
                // sleep(6);
                // chara->state=MOVE1;// Set state to conceal
                //}
            }
            // if (chara->gif_status[chara->state]->done) {
            // chara->state = STOP1;
            // atkcount+=1;
            // printf("%d\n",atkcount);
            // chara->new_proj_monster1 = false;
            //}
            /*if(atkcount==5){
                atkcount=0;
                chara->state = CONCEAL1;
            }*/
            if (chara->gif_status[ATK1]->display_index == 2 && chara->new_proj_monster1 == false)
            {
                Elements *pro;
                if (chara->dir_monster1)
                {
                    pro = New_Projectile_monster1(Projectile_monster1_L,
                                                  chara->x - 50,
                                                  chara->y + 10,
                                                  -9);
                }
                else
                {
                    pro = New_Projectile_monster1(Projectile_monster1_L,
                                                  chara->x + chara->width - 100,
                                                  chara->y + 10,
                                                  9);
                }
                _Register_elements(scene, pro);
                chara->new_proj_monster1 = true;
            }
        }

        if(atkcount==10){
            atkcount=0;
             chara->mons2state = ANGRYWALK1;
        }

         
    }

    if((chara->mons2state==DIE1))
    {
        al_play_sample_instance(chara->sample_instance_dies);
        if((chara->gif_status[DIE1]->done)){
        change_window=2;
        ele->dele=true;
        }
    }

    /*if(chara->life==0){
        change_window=2;
        ele->dele=true;
    }*/
}

void monster1_draw(Elements *const ele)
{
    // with the state, draw corresponding image
    monster1 *chara = ((monster1 *)(ele->pDerivedObj));
    ALLEGRO_BITMAP *frame = algif_get_bitmap(chara->gif_status[chara->mons2state], al_get_time());
    if (frame)
    {
        al_draw_bitmap(frame, chara->x, chara->y, ((chara->dir_monster1) ? ALLEGRO_FLIP_HORIZONTAL : 0));
        hp_bar((WIDTH-chara->full_life)-50,50,chara->full_life,30,chara->life);
    }
    if (chara->mons2state == ATK && chara->gif_status[chara->mons2state]->display_index == 2)
    {
        al_play_sample_instance(chara->atk_Sound);
    }
}
void monster1_destory(Elements *const ele)
{
    monster1 *Obj = ((monster1 *)(ele->pDerivedObj));
    al_destroy_sample_instance(Obj->atk_Sound);
    for (int i = 0; i < 7; i++){
        algif_destroy_animation(Obj->gif_status[i]);
    }
    al_destroy_sample(Obj->dies);
    al_destroy_sample_instance(Obj->sample_instance_dies);
    free(Obj->hitbox);
    free(Obj);
    free(ele);
}

void _monster1_update_position(Elements *const ele, int dx, int dy)
{
    monster1 *chara = ((monster1 *)(ele->pDerivedObj));
    chara->x += dx;
    chara->y += dy;
    Shape *hitbox = chara->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}

// void monster1_interact(Elements *const self, Elements *const target) {}
