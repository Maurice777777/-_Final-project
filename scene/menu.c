//menu.c
#include <allegro5/allegro_primitives.h>
#include "menu.h"
#include <stdbool.h>
/*
   [Menu function]
*/
Scene *New_Menu(int label)
{
    Menu *pDerivedObj = (Menu *)malloc(sizeof(Menu));
    Scene *pObj = New_Scene(label);
    pDerivedObj->background = al_load_bitmap("assets/image/menu.png");
    pDerivedObj->start = al_load_bitmap("assets/image/start.png"); // 載入圖檔
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 12, 0);
    // Load sound
    pDerivedObj->song = al_load_sample("assets/sound/menu.mp3");
    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    pDerivedObj->title_x = WIDTH / 2;
    pDerivedObj->title_y = HEIGHT / 2;
    // 初始化start的位置和大小
    pDerivedObj->target_x = 470; 
    pDerivedObj->target_y = 650; 
    pDerivedObj->target_width = 987; 
    pDerivedObj->target_height = 146; 
    // Loop the song until the display closes
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.4);
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = menu_update;
    pObj->Draw = menu_draw;
    pObj->Destroy = menu_destroy;
    return pObj;
}
// void menu_update(Scene *self)
// {
//     if (key_state[ALLEGRO_KEY_ENTER])
//     {
//         self->scene_end = true;
//         window = 1;
//     }
//     return;
// }
void menu_draw(Scene *self)
{
    Menu *Obj = ((Menu *)(self->pDerivedObj));
    al_clear_to_color(al_map_rgb(0, 0, 0));
    Menu *gs = ((Menu *)(self->pDerivedObj));
    al_draw_bitmap(gs->background, 0, 0, 0);
    al_draw_bitmap(gs->start, 470, 650, 0); 
    //al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->title_x, Obj->title_y, ALLEGRO_ALIGN_CENTRE, "Press 'Enter' to start");
    //al_draw_rectangle(Obj->title_x - 150, Obj->title_y - 30, Obj->title_x + 150, Obj->title_y + 30, al_map_rgb(255, 255, 255), 0);
    al_play_sample_instance(Obj->sample_instance);
}
void menu_destroy(Scene *self)
{
    Menu *Obj = ((Menu *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background;
    al_destroy_bitmap(background);
    al_destroy_font(Obj->font);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    free(Obj);
    free(self);
}

void menu_update(Scene *self)
{
    Menu *Obj = ((Menu *)(self->pDerivedObj));
    ALLEGRO_MOUSE_STATE state;
    al_get_mouse_state(&state);

    if (al_mouse_button_down(&state, 1)) // 檢查滑鼠左鍵是否被按下
    {
        printf("HI\n");
        // 檢查滑鼠的位置是否在你的目標區域內
        if (state.x >= Obj->target_x && state.x <= Obj->target_x + Obj->target_width &&
            state.y >= Obj->target_y && state.y <= Obj->target_y + Obj->target_height)
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
