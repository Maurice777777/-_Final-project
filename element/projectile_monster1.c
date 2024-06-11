#include "projectile_monster1.h"
#include "../shapes/Circle.h"
/*
   [Projectile function]
*/
Elements *New_Projectile_monster1(int label, int x, int y, int v)
{
    Projectile_monster1 *pDerivedObj = (Projectile_monster1 *)malloc(sizeof(Projectile_monster1));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/projectile_monster1.png");
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
    pObj->Update = Projectile_monster1_update;
    pObj->Interact = Projectile_monster1_interact;
    pObj->Draw = Projectile_monster1_draw;
    pObj->Destroy = Projectile_monster1_destory;

    return pObj;
}
void Projectile_monster1_update(Elements *const ele)
{
    Projectile_monster1 *Obj = ((Projectile_monster1 *)(ele->pDerivedObj));
    _Projectile_monster1_update_position(ele, (Obj->v), 0);
}
void _Projectile_monster1_update_position(Elements *const self, int dx, int dy)
{
    Projectile_monster1 *Obj = ((Projectile_monster1 *)(self->pDerivedObj));
    Obj->x += dx;
    Obj->y += dy;
    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}

/*void Projectile_monster1_interact(Elements *self, Elements *_tar)
{
    Projectile_monster1 *obj = ((Projectile_monster1 *)(self->pDerivedObj));
    Hero* tar=(Hero*)(_tar->pDerivedObj);
    if(abs(obj->x-tar->x)<3){
        self->dele = true;
        tar->life-=tar->life>=15?15:tar->life;
        tar->state=atked;
    }
}*/

void Projectile_monster1_interact(Elements *const self_ele, Elements *const ele)
{
    Projectile_monster1 *Obj = ((Projectile_monster1 *)(self_ele->pDerivedObj));
    Hero *charc = ((Hero *)(ele->pDerivedObj));
    if (ele->label == Floor2_L)
    {
        if (Obj->x < 0 - Obj->width)
            self_ele->dele = true;
        else if (Obj->x > WIDTH + Obj->width)
            self_ele->dele = true;
    }
    else if (ele->label == Hero2_L)
    {
        if (charc->hitbox->overlap(charc->hitbox, Obj->hitbox))
        {
        self_ele->dele = true;
        charc->life-=charc->life>=25?25:charc->life;
        charc->state=atked;
        
        }
    }
}

void Projectile_monster1_draw(Elements *const ele)
{
    Projectile_monster1 *Obj = ((Projectile_monster1 *)(ele->pDerivedObj));
    if (Obj->v > 0)
        al_draw_bitmap(Obj->img, Obj->x, Obj->y, ALLEGRO_FLIP_HORIZONTAL);
    else
         al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Projectile_monster1_destory(Elements *const ele)
{
    Projectile_monster1 *Obj = ((Projectile_monster1 *)(ele->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(ele);
}
