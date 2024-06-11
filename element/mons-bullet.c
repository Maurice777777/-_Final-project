#include "mons-bullet.h"
#include "../shapes/Circle.h"
/*
   [Projectile function]
*/
Elements *New_Monsbullet(int label, int x, int y, int v)//生成時初始化條件
{
    Monsbullet *pDerivedObj = (Monsbullet *)malloc(sizeof(Monsbullet));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->gif = algif_new_gif("assets/image/monster/bullet/bullet.gif", -1);
    
    pDerivedObj->width = pDerivedObj->gif->width;
    pDerivedObj->height = pDerivedObj->gif->height;
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->v = v;
    
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x + pDerivedObj->width / 2,
                                     pDerivedObj->y + pDerivedObj->height / 2,
                                     min(pDerivedObj->width, pDerivedObj->height) / 2);
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Hero_L;
    
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Monsbullet_update;
    pObj->Interact = Monsbullet_interact;
    pObj->Draw = Monsbullet_draw;
    pObj->Destroy = Monsbullet_destory;
    
    return pObj;
}
void Monsbullet_update(Elements *self)//每貞做怎樣的事情
{
    _Monsbullet_update_position(self, ((Monsbullet *)(self->pDerivedObj))->v, 0);
}
void _Monsbullet_update_position(Elements *self, int dx, int dy)
{
    Monsbullet *Obj = ((Monsbullet *)(self->pDerivedObj));
    Obj->x += dx;
    Obj->y += dy;
    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}
void Monsbullet_interact(Elements *self, Elements *_tar)
{
    Monsbullet *obj = ((Monsbullet *)(self->pDerivedObj));
    Hero* tar=(Hero*)(_tar->pDerivedObj);
    if((obj->hitbox->overlap(obj->hitbox, tar->hitbox))&&(tar->state!=dodge)){
        self->dele = true;
        tar->life-=tar->life>=15?15:tar->life;
        tar->state=atked;
    }
}
void Monsbullet_draw(Elements *self)
{
    Monsbullet *obj = ((Monsbullet *)(self->pDerivedObj));
    ALLEGRO_BITMAP *frame = algif_get_bitmap(obj->gif, al_get_time());
    
    if (obj->v > 0)
        al_draw_bitmap(frame, obj->x, obj->y, ALLEGRO_FLIP_HORIZONTAL);
    else
       al_draw_bitmap(frame, obj->x, obj->y, 0);
}
void Monsbullet_destory(Elements *self)
{
    Monsbullet *Obj = ((Monsbullet *)(self->pDerivedObj));
    algif_destroy_animation(Obj->gif);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
