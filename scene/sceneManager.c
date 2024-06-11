#include "sceneManager.h"
#include "menu.h"
#include "chara1_choose.h"
#include "chara2_choose.h"
#include "gamescene.h"
#include "gamescene2.h"
#include "winscene.h"
#include "gg_scene.h"
#include "l_scene.h"
#include "hero1info.h"
#include "hero2info.h"

Scene *scene = NULL;
void create_scene(SceneType type)
{
    printf("t=%d\n",type);
    switch (type)
    {
    case Menu_L:
        scene = New_Menu(Menu_L);
        break;
    case GameScene_L:
        scene = New_GameScene(GameScene_L);
        break;
    case GameScene2_L:
        //printf("有進去嗎\n");
        scene = New_GameScene2(GameScene2_L);
        break;
    case WinScene_L:
        //printf("in 2 \n");
        scene = New_Winscene(WinScene_L);
        break;
    case GgScene_L:
        scene = New_ggscene(GgScene_L);
        break;
    case Ch1c_L:
        scene = New_ch1c(Ch1c_L);
        break;
    case Lscene_L:
        scene = New_l_scene(Lscene_L);
        break;
    case Hero1info_L:
        scene = hero1info_scene(Hero1info_L);
        break;
    case Hero2info_L:
        scene = hero2info_scene(Hero2info_L);
        break;
    case Ch2c_L:
        scene = New_ch2c(Ch2c_L);
        break;
    
    default:
        break;
    }
}