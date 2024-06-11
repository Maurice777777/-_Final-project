#include <allegro5/allegro_primitives.h>
#include "hero1info.h"
#include <stdbool.h>
/*
   [Ggscene function]
*/
Scene *hero1info_scene(int label)
{
    printf("come into hero1info");
    h1info *pDerivedObj = (h1info *)malloc(sizeof(h1info));
    Scene *pObj = New_Scene(label);
    pDerivedObj->background = al_load_bitmap("assets/image/hero1info.png");
    pDerivedObj->back = al_load_bitmap("assets/image/back.png");
    //pDerivedObj->restart = al_load_bitmap("assets/image/restart.png"); // 載入圖檔
    //pDerivedObj->background = al_load_bitmap("assets/image/level2.png");

    pDerivedObj->song = al_load_sample("assets/sound/ch1c_bgm.mp3");
    al_reserve_samples(60);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.1);

    // setting derived object member
    //pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 12, 0);
    // Load sound
    //pDerivedObj->title_x = WIDTH / 2;
    //pDerivedObj->title_y = HEIGHT / 2;

    pDerivedObj->back_x = 10; 
    pDerivedObj->back_y = 10; 
    pDerivedObj->back_width = 70; 
    pDerivedObj->back_height = 56; 

    // 初始化start的位置和大小
    /*pDerivedObj->target_x = 450; 
    pDerivedObj->target_y = 700; 
    pDerivedObj->target_width = 400; 
    pDerivedObj->target_height = 200; */
    // Loop the song until the display closes
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = hero1info_update;
    pObj->Draw = hero1info_draw;
    pObj->Destroy = hero1info_destroy;
    return pObj;
}

void hero1info_update(Scene *self)
{
    // if (key_state[ALLEGRO_KEY_ENTER])
    // {
    //     self->scene_end = true;
    //     window = 1;
    // }
    // return;
    h1info *Obj = ((h1info *)(self->pDerivedObj));
    ALLEGRO_MOUSE_STATE state;
    al_get_mouse_state(&state);

    if (al_mouse_button_down(&state, 1)) // 檢查滑鼠左鍵是否被按下
    {
        printf("HI\n");
        // 檢查滑鼠的位置是否在你的目標區域內
        if(state.x >= Obj->back_x && state.x <= Obj->back_x + Obj->back_width &&
               state.y >= Obj->back_y && state.y <= Obj->back_y + Obj->back_height)
        {
            Obj->click = al_load_sample("assets/sound/click.mp3");
            al_reserve_samples(10);
            Obj->sample_instance_click = al_create_sample_instance(Obj->click);
            al_set_sample_instance_playmode(Obj->sample_instance_click, ALLEGRO_PLAYMODE_ONCE);
            al_restore_default_mixer();
            al_attach_sample_instance_to_mixer(Obj->sample_instance_click, al_get_default_mixer());
            // set the volume of instance
            al_set_sample_instance_gain(Obj->sample_instance_click, 0.3);
            al_play_sample_instance(Obj->sample_instance_click);
            self->scene_end = true;
            window = 5; // 跳轉到下一個畫面
        }
    }
}
void hero1info_draw(Scene *self)
{
    //h1info* Obj = ((h1info *)(self->pDerivedObj));
    al_clear_to_color(al_map_rgb(0, 0, 0));
    h1info *gs = ((h1info *)(self->pDerivedObj));
    al_draw_bitmap(gs->background, 0, 0, 0);
    //al_draw_bitmap(gs->restart, 800, 800, 0); 
    al_draw_bitmap(gs->back, 5, 5, 0); 
    //al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->title_x, Obj->title_y, ALLEGRO_ALIGN_CENTRE, "Press 'Enter' to start");
    //al_draw_rectangle(Obj->title_x - 150, Obj->title_y - 30, Obj->title_x + 150, Obj->title_y + 30, al_map_rgb(255, 255, 255), 0);
    al_play_sample_instance(gs->sample_instance);
}
void hero1info_destroy(Scene *self)
{
    h1info *Obj = ((h1info *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background;
    al_destroy_bitmap(background);
    //al_destroy_font(Obj->font);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    free(Obj);
    free(self);
}
