#include <allegro5/allegro_primitives.h>
#include <stdbool.h>
#include "gamescene.h"
//#include "../element/monster.h"
/*
   [GameScene function]
*/
Scene *New_GameScene(int label)
{
    GameScene *pDerivedObj = (GameScene *)malloc(sizeof(GameScene));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->background = al_load_bitmap("assets/image/level1.png");
    pDerivedObj->song_gs = al_load_sample("assets/sound/stage1_bgm.mp3");
    al_reserve_samples(60);
    pDerivedObj->sample_instance_gs = al_create_sample_instance(pDerivedObj->song_gs);
    al_set_sample_instance_playmode(pDerivedObj->sample_instance_gs, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance_gs, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance_gs, 0.2);
    pObj->pDerivedObj = pDerivedObj;
    // register element
    //_Register_elements(pObj, New_Floor(Floor_L));
    //_Register_elements(pObj, New_Teleport(Teleport_L));
    //_Register_elements(pObj, New_Tree(Tree_L));
    //_Register_elements(pObj, New_Character(Character_L));
    _Register_elements(pObj, New_Monster(Monster_L));
    _Register_elements(pObj, New_Hero(Hero_L));
    //_Register_elements(pObj, New_Monster(Monsbullet_L));
    // setting derived object function
    pObj->Update = game_scene_update;
    pObj->Draw = game_scene_draw;
    pObj->Destroy = game_scene_destroy;
    return pObj;
}
void game_scene_update(Scene *self)
{
    // update every element
    ElementVec allEle = _Get_all_elements(self);
    //Monster *mons = (Monster *)malloc(sizeof(Monster));
    //Monster *elf = mons->life;
    for (int i = 0; i < allEle.len; i++)
    {
        allEle.arr[i]->Update(allEle.arr[i]);
    }

    // run interact for every element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        // run every interact object
        for (int j = 0; j < ele->inter_len; j++)
        {
            int inter_label = ele->inter_obj[j];
            ElementVec labelEle = _Get_label_elements(self, inter_label);
            for (int i = 0; i < labelEle.len; i++)
            {
                ele->Interact(ele, labelEle.arr[i]);
            }
        }
    }
    // remove element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        if (ele->dele)
            _Remove_elements(self, ele);
    }

    if(change_window==1)
    {
        self->scene_end = true;
        window = 4;
        change_window=0;
    }else if(change_window==2){
        self->scene_end = true;
        window = 2;
        change_window=0;
    }
    else if(change_window==3)
    {
        self->scene_end = true;
        window = 6;
        change_window=0;
    }

    // if (key_state[ALLEGRO_KEY_P])
    // {
    //     self->scene_end = true;
    //     window = 3;
    // }
    // return;
}
void game_scene_draw(Scene *self)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    GameScene *gs = ((GameScene *)(self->pDerivedObj));
    al_draw_bitmap(gs->background, 0, 0, 0);
    al_play_sample_instance(gs->sample_instance_gs);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }
}
void game_scene_destroy(Scene *self)
{
    printf("in d\n");
    GameScene *Obj = ((GameScene *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background;
    al_destroy_bitmap(background);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        printf("%d %d\n",i,ele->label);
        ele->Destroy(ele);
        printf("%d\n",i);
    }
    al_destroy_sample(Obj->song_gs);
    al_destroy_sample_instance(Obj->sample_instance_gs);
    free(Obj);
    free(self);
    printf("d all \n");
}