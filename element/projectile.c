#include "projectile.h"
#include "../shapes/Circle.h"
/*
   [Projectile function]
*/
Elements *Newcharacter_Projectile(int label, int x, int y, int v)
{
    Projectile_chara *pDerivedObj = (Projectile_chara *)malloc(sizeof(Projectile_chara));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/wave.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x;
    pDerivedObj->y = HEIGHT - pDerivedObj->height-300;
    pDerivedObj->v = v;
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x + pDerivedObj->width / 2,
                                     pDerivedObj->y + pDerivedObj->height / 2,
                                     min(pDerivedObj->width, pDerivedObj->height) / 2);
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Tree_L;
    pObj->inter_obj[pObj->inter_len++] = Floor_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Projectile_character_update;
    pObj->Interact = Projectile_character_interact;
    pObj->Draw = Projectile_character_draw;
    pObj->Destroy = Projectile_character_destory;

    return pObj;
}
void Projectile_character_update(Elements *const ele)
{
    Projectile_chara *Obj = ((Projectile_chara *)(ele->pDerivedObj));
    _Projectile_character_update_position(ele, (Obj->v), 0);
}
void _Projectile_character_update_position(Elements *const self, int dx, int dy)
{
    Projectile_chara *Obj = ((Projectile_chara *)(self->pDerivedObj));
    Obj->x -= dx;
    Obj->y -= dy;
    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}
void Projectile_character_interact(Elements *const self_ele, Elements *const ele)
{
    Projectile_chara *Obj = ((Projectile_chara *)(self_ele->pDerivedObj));
    if (ele->label == Floor_L)
    {
        if (Obj->x < 0 - Obj->width)
            self_ele->dele = true;
        else if (Obj->x > WIDTH + Obj->width)
            self_ele->dele = true;
    }
    else if (ele->label == Tree_L)
    {
        Tree *tree = ((Tree *)(ele->pDerivedObj));
        if (tree->hitbox->overlap(tree->hitbox, Obj->hitbox))
        {
            self_ele->dele = true;
        }
    }
}
void Projectile_character_draw(Elements *const ele)
{
    Projectile_chara *Obj = ((Projectile_chara *)(ele->pDerivedObj));
    if (Obj->v > 0)
        al_draw_bitmap(Obj->img, Obj->x, Obj->y, ALLEGRO_FLIP_HORIZONTAL);
    else
        al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Projectile_character_destory(Elements *const ele)
{
    Projectile_chara *Obj = ((Projectile_chara *)(ele->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(ele);
}
