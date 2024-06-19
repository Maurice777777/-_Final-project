//ch1c.c
#include <allegro5/allegro_primitives.h>
#include "chara1_choose.h"
#include <stdbool.h>
/*
   [Menu function]
*/

Scene *New_ch1c(int label)
{
    printf("come in to ch1c~\n");
    ch1c *pDerivedObj = (ch1c *)malloc(sizeof(ch1c));
    Scene *pObj = New_Scene(label);
    //if(r==0){
    _Register_elements(pObj, New_Hero(Heroc1c_L));
    /*}else if(r==1){
    _Register_elements(pObj, New_Character(Characterc1c_L));
    }*/
    pDerivedObj->background = al_load_bitmap("assets/image/chara1_choose.png");
    printf("+++\n");
    pDerivedObj->start = al_load_bitmap("assets/image/select.png"); // 載入圖檔
    printf("???");
    //返回的圖按鈕
    pDerivedObj->back = al_load_bitmap("assets/image/back.png");
    pDerivedObj->hero1info = al_load_bitmap("assets/image/infoicon.png"); 
    //換角色
    pDerivedObj->rselect = al_load_bitmap("assets/image/select_right.png");
    //pDerivedObj->start = al_load_bitmap("assets/image/select.png"); // 載入圖檔
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 12, 0);
    // Load sound
    pDerivedObj->song = al_load_sample("assets/sound/ch1c_bgm.mp3");
    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    pDerivedObj->title_x = WIDTH / 2;
    pDerivedObj->title_y = HEIGHT / 2;
    // 初始化start的位置和大小
    pDerivedObj->target_x = 850; 
    pDerivedObj->target_y = 720; 
    pDerivedObj->target_width = 200; 
    pDerivedObj->target_height = 64; 
    // 初始化back的位置和大小
    pDerivedObj->back_x = 10; 
    pDerivedObj->back_y = 10; 
    pDerivedObj->back_width = 70; 
    pDerivedObj->back_height = 56; 
     // 初始化hero1info的位置和大小
    pDerivedObj->hero1info_x = 1747; 
    pDerivedObj->hero1info_y = 10; 
    pDerivedObj->hero1info_width = 163; 
    pDerivedObj->hero1info_height = 162; 
    //換角色(右)
    pDerivedObj->rselect_x = 1500; 
    pDerivedObj->rselect_y = 500; 
    pDerivedObj->rselect_width = 54; 
    pDerivedObj->rselect_height = 56; 
    // Loop the song until the display closes
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.2);
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = ch1c_update;
    pObj->Draw = ch1c_draw;
    pObj->Destroy = ch1c_destroy;
    printf(":::::\n");
    return pObj;
}
//void ch1c_update(Scene *self){
    
//}
// {
//     if (key_state[ALLEGRO_KEY_ENTER])
//     {
//         self->scene_end = true;
//         window = 1;
//     }
//     return;
// }
void ch1c_draw(Scene *self)
{
    printf(",l,l");
    ch1c  *Obj = ((ch1c *)(self->pDerivedObj));
    al_clear_to_color(al_map_rgb(0, 0, 0));
    //ch1c *gs = ((ch1c *)(self->pDerivedObj));
    al_draw_bitmap(Obj->background, 0, 0, 0);
    al_draw_bitmap(Obj->start, 850, 720, 0); 
    al_draw_bitmap(Obj->back, 5, 5, 0); 
    al_draw_bitmap(Obj->hero1info, 1747, 10, 0); 
    al_draw_bitmap(Obj->rselect, 1500, 500, 0); 
    //al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->title_x, Obj->title_y, ALLEGRO_ALIGN_CENTRE, "Press 'Enter' to start");
    //al_draw_rectangle(Obj->title_x - 150, Obj->title_y - 30, Obj->title_x + 150, Obj->title_y + 30, al_map_rgb(255, 255, 255), 0);
    al_play_sample_instance(Obj->sample_instance);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }
}
void ch1c_destroy(Scene *self)
{
    ch1c *Obj = ((ch1c *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background;
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        printf("%d %d\n",i,ele->label);
        ele->Destroy(ele);
        printf("%d\n",i);
    }
    al_destroy_bitmap(background);
    al_destroy_font(Obj->font);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    free(Obj);
    free(self);
}

void ch1c_update(Scene *self)
{
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
    ch1c *Obj = ((ch1c *)(self->pDerivedObj));
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
            window = 1; // 跳轉到下一個畫面
        }
        //返回
        else if(state.x >= Obj->back_x && state.x <= Obj->back_x + Obj->back_width &&
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
            window = 0; // 跳轉到下一個畫面
        }
        //資訊
        else if(state.x >= Obj->hero1info_x && state.x <= Obj->hero1info_x + Obj->hero1info_width &&
               state.y >= Obj->hero1info_y && state.y <= Obj->hero1info_y + Obj->hero1info_height)
        {
            printf("??");
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
            window = 7; // 跳轉到下一個畫面
        }
        else if(state.x >= Obj->rselect_x && state.x <= Obj->rselect_x + Obj->rselect_width &&
               state.y >= Obj->rselect_y && state.y <= Obj->rselect_y + Obj->rselect_height)
        {
            printf("ioioppp");
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
            window = 9; // 跳轉到下一個畫面
        }
    }
    
}
