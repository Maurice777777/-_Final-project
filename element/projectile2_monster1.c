#include "projectile2_monster1.h"
#include "../shapes/Circle.h"
/*
   [Projectile function]
*/
Elements *New_Projectile2_monster1(int label, int x, int y, int v)
{
    Projectile2_monster1 *pDerivedObj = (Projectile2_monster1 *)malloc(sizeof(Projectile2_monster1));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/projectile2_monster1.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x;
    pDerivedObj->y = y+300;
    pDerivedObj->v = v;
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x + pDerivedObj->width / 2,
                                     pDerivedObj->y + pDerivedObj->height / 2,
                                     min(pDerivedObj->width, pDerivedObj->height) / 2);
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Hero2_L;
    pObj->inter_obj[pObj->inter_len++] = Floor2_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Projectile2_monster1_update;
    pObj->Interact = Projectile2_monster1_interact;
    pObj->Draw = Projectile2_monster1_draw;
    pObj->Destroy = Projectile2_monster1_destory;

    return pObj;
}
void Projectile2_monster1_update(Elements *const ele)
{
    Projectile2_monster1 *Obj = ((Projectile2_monster1 *)(ele->pDerivedObj));
    _Projectile2_monster1_update_position(ele, 0, (Obj->v));
}
void _Projectile2_monster1_update_position(Elements *const self, int dx, int dy)
{
    Projectile2_monster1 *Obj = ((Projectile2_monster1 *)(self->pDerivedObj));
    Obj->x += dx;
    Obj->y += dy;
    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}
void Projectile2_monster1_interact(Elements *const self_ele, Elements *const ele)
{
    Projectile2_monster1 *Obj = ((Projectile2_monster1 *)(self_ele->pDerivedObj));
    if (ele->label == Floor2_L)
    {
        if (Obj->y>HEIGHT)
            self_ele->dele = true;
    }
    else if (ele->label == Hero2_L)
    {
        Hero *charc = ((Hero *)(ele->pDerivedObj));
        if (charc->hitbox->overlap(charc->hitbox, Obj->hitbox))
        {
            self_ele->dele = true;
            charc->life-=charc->life>=15?15:charc->life;
            //charc->state=atked;
        }
    }
}
void Projectile2_monster1_draw(Elements *const ele)
{
    Projectile2_monster1 *Obj = ((Projectile2_monster1 *)(ele->pDerivedObj));
    if (Obj->v > 0)
        al_draw_bitmap(Obj->img, Obj->x, Obj->y, ALLEGRO_FLIP_HORIZONTAL);
    else
        al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Projectile2_monster1_destory(Elements *const ele)
{
    Projectile2_monster1 *Obj = ((Projectile2_monster1 *)(ele->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(ele);
}