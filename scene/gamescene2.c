#include "gamescene2.h"
/*
   [GameScene function]
*/
Scene *New_GameScene2(int label)
{
    GameScene2 *pDerivedObj = (GameScene2 *)malloc(sizeof(GameScene2));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->background = al_load_bitmap("assets/image/level2.png");
    pDerivedObj->song = al_load_sample("assets/sound/stage2_bgm.mp3");
    al_reserve_samples(60);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.3);
    pObj->pDerivedObj = pDerivedObj;
    // register element
    //_Register_elements(pObj, New_Floor(Floor2_L));
    //_Register_elements(pObj, New_Teleport(Teleport2_L));
    //_Register_elements(pObj, New_Tree(Tree2_L));
    _Register_elements(pObj, New_Hero(Hero2_L));
    //_Register_elements(pObj, New_Ball(Ball2_L));
    _Register_elements(pObj, New_monster1(monster1_L));
    // setting derived object function
    pObj->Update = game_scene2_update;
    pObj->Draw = game_scene2_draw;
    pObj->Destroy = game_scene2_destroy;
    return pObj;
}
void game_scene2_update(Scene *const pGameSceneObj)
{
    // update every element
    ElementVec allEle = _Get_all_elements(pGameSceneObj);
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
            ElementVec labelEle = _Get_label_elements(pGameSceneObj, inter_label);
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
            _Remove_elements(pGameSceneObj, ele);
    }
    if (change_window==1)
    {
        pGameSceneObj->scene_end = true;
        window = 4;
        change_window=0;
    }else if(change_window==2){
        pGameSceneObj->scene_end = true;
        window = 3;
        change_window=0;
    }
    //return;
}
void game_scene2_draw(Scene *const pGameSceneObj)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    GameScene2 *gs = ((GameScene2 *)(pGameSceneObj->pDerivedObj));
    al_draw_bitmap(gs->background, 0, 0, 0);
    al_play_sample_instance(gs->sample_instance);

    ElementVec allEle = _Get_all_elements(pGameSceneObj);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }
}
void game_scene2_destroy(Scene *const pGameSceneObj)
{
    GameScene2 *Obj = ((GameScene2 *)(pGameSceneObj->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background;
    al_destroy_bitmap(background);
    ElementVec allEle = _Get_all_elements(pGameSceneObj);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Destroy(ele);
    }
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    free(Obj);
    free(pGameSceneObj);
}