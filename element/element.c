#include "element.h"
#include <stdbool.h>
#include  <allegro5/allegro_primitives.h>
/*
   [Element function]
*/
Elements *New_Elements(int label)
{
    Elements *pObj;
    pObj = (Elements *)malloc(sizeof(Elements));
    pObj->inter_len = 0;
    pObj->dele = false;
    // setting object member
    pObj->label = label;
    pObj->pDerivedObj = pObj;
    return pObj;
}
void hp_bar(int x,int y,int w,int h,int rest){
    //al_draw_rounded_rectangle(x, y, x+w, y+h,1,1,al_map_rgb(255,0,0),2);
    al_draw_rectangle(x, y, x+w, y+h,al_map_rgb(255,0,0),1);
    if(((double)rest)/((double)w)>0.35){
    al_draw_filled_rounded_rectangle(x, y, x+rest,y+h,1,1, al_map_rgb(255,0,0));
    }else{
        al_draw_filled_rounded_rectangle(x, y, x+rest,y+h,1,1, al_map_rgb(255,165,0));
    }
}
