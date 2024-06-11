#include <allegro5/allegro_primitives.h>
#include "l_scene.h"
#include <stdbool.h>
/*
   [Ggscene function]
*/
Scene *New_l_scene(int label)
{
    ll *pDerivedObj = (ll *)malloc(sizeof(ll));
    Scene *pObj = New_Scene(label);
    pDerivedObj->background = al_load_bitmap("assets/image/lose_scene.png");
    pDerivedObj->restart = al_load_bitmap("assets/image/restart.png"); // 載入圖檔
    //pDerivedObj->background = al_load_bitmap("assets/image/level2.png");

    pDerivedObj->song = al_load_sample("assets/sound/ggscene_bgm.mp3");
    al_reserve_samples(60);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.1);

    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 12, 0);
    // Load sound
    pDerivedObj->title_x = WIDTH / 2;
    pDerivedObj->title_y = HEIGHT / 2;
    // 初始化restart的位置和大小
    pDerivedObj->target_x = 800; 
    pDerivedObj->target_y = 950; 
    pDerivedObj->target_width = 300; 
    pDerivedObj->target_height = 47; 
    // Loop the song until the display closes
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = ll_update;
    pObj->Draw = ll_draw;
    pObj->Destroy = ll_destroy;
    return pObj;
}
void ll_update(Scene *self)
{
    // if (key_state[ALLEGRO_KEY_ENTER])
    // {
    //     self->scene_end = true;
    //     window = 1;
    // }
    // return;
    ll *Obj = ((ll *)(self->pDerivedObj));
    ALLEGRO_MOUSE_STATE state;
    al_get_mouse_state(&state);

    if (al_mouse_button_down(&state, 1)) // 檢查滑鼠左鍵是否被按下
    {
        printf("HI\n");
        // 檢查滑鼠的位置是否在你的目標區域內
        if (state.x >= Obj->target_x && state.x <= Obj->target_x + Obj->target_width &&
            state.y >= Obj->target_y && state.y <= Obj->target_y + Obj->target_height)
        {
            printf("here\n");
            self->scene_end = true;
            window = 0; // 跳轉到下一個畫面
        }
    }
}
void ll_draw(Scene *self)
{
    ll* Obj = ((ll *)(self->pDerivedObj));
    al_clear_to_color(al_map_rgb(0, 0, 0));
    ll *gs = ((ll *)(self->pDerivedObj));
    al_draw_bitmap(gs->background, 0, 0, 0);
    al_draw_bitmap(gs->restart, 800, 950, 0); 
    //al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->title_x, Obj->title_y, ALLEGRO_ALIGN_CENTRE, "Press 'Enter' to start");
    //al_draw_rectangle(Obj->title_x - 150, Obj->title_y - 30, Obj->title_x + 150, Obj->title_y + 30, al_map_rgb(255, 255, 255), 0);
    al_play_sample_instance(Obj->sample_instance);
}
void ll_destroy(Scene *self)
{
    ll *Obj = ((ll *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background;
    al_destroy_bitmap(background);
    al_destroy_font(Obj->font);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    free(Obj);
    free(self);
}
