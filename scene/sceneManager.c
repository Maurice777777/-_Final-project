#include "sceneManager.h"
#include "menu.h"
#include "gamescene.h"
#include "winscene.h"
#include "gg_scene.h"
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
    case WinScene_L:
        scene = New_Winscene(WinScene_L);
        break;
    case GgScene_L:
        scene = New_ggscene(GgScene_L);
        break;
    default:
        break;
    }
}