#include "character.h"
#include "../scene/sceneManager.h"
#include "projectile.h"
//#include "projectile_character.h"
#include "../shapes/Rectangle.h"
#include "../algif5/src/algif.h"
#include "../global.h"
#include <stdio.h>
/*
   [Character function]
*/
Elements *New_Character(int label)
{
    Character *pDerivedObj = (Character *)malloc(sizeof(Character));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    // load character images
    char state_string[4][10] = {"stand", "run", "shoot1","shoot2"};
    for (int i = 0; i < 4; i++)
    {
        char buffer[50];
        sprintf(buffer, "assets/image/charact2-%s.gif", state_string[i]);
        pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    }
    // load effective sound
    ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/atk_sound.wav");
    pDerivedObj->atk_Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pDerivedObj->atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->atk_Sound, al_get_default_mixer());

    // initial the geometric information of character
    pDerivedObj->width = pDerivedObj->gif_status[0]->width;
    pDerivedObj->height = pDerivedObj->gif_status[0]->height;
    pDerivedObj->x = WIDTH/2-50;//910
    pDerivedObj->y = HEIGHT/2-280;
    //pDerivedObj->x = 300;
    //pDerivedObj->y = HEIGHT - pDerivedObj->height;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);
    pDerivedObj->dir = false; // true: face to right, false: face to left
    // initial the animation component
    pDerivedObj->state = STOP;
    pDerivedObj->new_proj = false;
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Draw = Character_draw;
    pObj->Update = Character_update;
    pObj->Interact = Character_interact;
    pObj->Destroy = Character_destory;
    return pObj;
}

void Character_update(Elements *const ele)
{
    // use the idea of finite state machine to deal with different state
    Character *chara = ((Character *)(ele->pDerivedObj));
    int yy = chara->y;
    if (chara->state == STOP)
    {
        if (key_state[ALLEGRO_KEY_SPACE])
        {
            chara->state = ATK;
            chara->y-=30;
        }
        else if (key_state[ALLEGRO_KEY_K])
        {
            chara->state = ATK2;
            chara->y-=30;
        }
        else if (key_state[ALLEGRO_KEY_A])
        {
            chara->dir = true;
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_D])
        {
            chara->dir = false;
            chara->state = MOVE;
        }
        else
        {
            chara->state = STOP;
        }
    }
    else if (chara->state == MOVE)
    {
        if (key_state[ALLEGRO_KEY_SPACE])
        {
            chara->state = ATK;
            chara->y-=30;
        }
        else if (key_state[ALLEGRO_KEY_K])
        {
            chara->state = ATK;
            chara->y-=30;
        }
        else if (key_state[ALLEGRO_KEY_A])
        {
            chara->dir = true;
            _Character_update_position(ele, -5, 0);
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_D])
        {
            chara->dir = false;
            _Character_update_position(ele, 5, 0);
            chara->state = MOVE;
        }
        if (chara->gif_status[chara->state]->done)
            chara->state = STOP;
    }
    else if (chara->state == ATK)
    {
        chara->y+=30;
        if (chara->gif_status[chara->state]->done) {
            chara->state = STOP;
            chara->new_proj = false;
        }
        if (chara->gif_status[ATK]->display_index == 2 && chara->new_proj == false)
        {
            Elements *pro;
            if (chara->dir)
            {
                pro = Newcharacter_Projectile(Projectile_L,
                                     chara->x + chara->width - 100,
                                     chara->y + 10,
                                     5);
            }
            else
            {
                pro = Newcharacter_Projectile(Projectile_L,
                                     chara->x - 50,
                                     chara->y + 10,
                                     -5);
            }
            _Register_elements(scene, pro);
            chara->new_proj = true;
        }
    }
    else if (chara->state == ATK2)
    {
        chara->y+=30;
        if (chara->gif_status[chara->state]->done) {
            chara->state = STOP;
            chara->new_proj = false;
        }
        if (chara->gif_status[ATK2]->display_index == 2 && chara->new_proj == false)
        {
            Elements *pro;
            if (chara->dir)
            {
                pro = Newcharacter_Projectile(Projectile_L,
                                     chara->x + chara->width - 100,
                                     chara->y + 10,
                                     5);
            }
            else
            {
                pro = Newcharacter_Projectile(Projectile_L,
                                     chara->x - 50,
                                     chara->y + 10,
                                     -5);
            }
            _Register_elements(scene, pro);
            chara->new_proj = true;
        }
    }
    if(chara->y!=yy) chara->y = yy;
}
void Character_draw(Elements *const ele)
{
    // with the state, draw corresponding image
    Character *chara = ((Character *)(ele->pDerivedObj));
    ALLEGRO_BITMAP *frame = algif_get_bitmap(chara->gif_status[chara->state], al_get_time());
    if (frame)
    {
        al_draw_bitmap(frame, chara->x, chara->y, ((chara->dir) ? ALLEGRO_FLIP_HORIZONTAL : 0));
    }
    if (chara->state == ATK && chara->gif_status[chara->state]->display_index == 2)
    {
        al_play_sample_instance(chara->atk_Sound);
    }
}
void Character_destory(Elements *const ele)
{
    Character *Obj = ((Character *)(ele->pDerivedObj));
    al_destroy_sample_instance(Obj->atk_Sound);
    for (int i = 0; i < 4; i++)
        algif_destroy_animation(Obj->gif_status[i]);
    free(Obj->hitbox);
    free(Obj);
    free(ele);
}

void _Character_update_position(Elements *const ele, int dx, int dy)
{
    Character *chara = ((Character *)(ele->pDerivedObj));
    chara->x += dx;
    chara->y += dy;
    Shape *hitbox = chara->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}

void Character_interact(Elements *const self, Elements *const target) {}