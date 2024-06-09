#include <allegro5/allegro_primitives.h>
#include "winscene.h"
#include <stdbool.h>
/*
   [Menu function]
*/
Scene *New_Winscene(int label)
{
    Winscene *pDerivedObj = (Winscene *)malloc(sizeof(Winscene));
    Scene *pObj = New_Scene(label);
    pDerivedObj->background = al_load_bitmap("assets/image/winscene.png");
    printf("蝦\n");
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 12, 0);
    // Load sound
    pDerivedObj->song = al_load_sample("assets/sound/menu.mp3");
    al_reserve_samples(20);
    printf("nice");
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    pDerivedObj->title_x = WIDTH / 2;
    pDerivedObj->title_y = HEIGHT / 2;
    // Loop the song until the display closes
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.1);
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = winscene_update;
    pObj->Draw = winscene_draw;
    pObj->Destroy = winscene_destroy;
    printf("nice");
    return pObj;
}
void winscene_update(Scene *self)
{
    if (key_state[ALLEGRO_KEY_ENTER])
    {
        self->scene_end = true;
        window = 0;
    }
    return;
}
void winscene_draw(Scene *self)
{
    Winscene *Obj = ((Winscene *)(self->pDerivedObj));
    al_clear_to_color(al_map_rgb(0, 0, 0));
    Winscene *gs = ((Winscene *)(self->pDerivedObj));
    al_draw_bitmap(gs->background, 0, 0, 0);
    //al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->title_x, Obj->title_y, ALLEGRO_ALIGN_CENTRE, "Press 'Enter' to start");
    //al_draw_rectangle(Obj->title_x - 150, Obj->title_y - 30, Obj->title_x + 150, Obj->title_y + 30, al_map_rgb(255, 255, 255), 0);
    al_play_sample_instance(Obj->sample_instance);
}
void winscene_destroy(Scene *self)
{
    Winscene *Obj = ((Winscene *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background;
    al_destroy_bitmap(background);
    al_destroy_font(Obj->font);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    free(Obj);
    free(self);
}
