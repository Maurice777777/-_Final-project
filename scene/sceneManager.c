#include "sceneManager.h"
#include "menu.h"
#include "gamescene.h"
#include "winscene.h"
Scene *scene = NULL;
void create_scene(SceneType type)
{
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
    default:
        break;
    }
}