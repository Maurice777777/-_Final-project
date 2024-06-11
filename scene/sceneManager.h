#ifndef SCENEMANAGER_H_INCLUDED
#define SCENEMANAGER_H_INCLUDED
#include "scene.h"
extern Scene *scene;
typedef enum SceneType
{
    Menu_L = 0,
    GameScene_L,
    GameScene2_L,
    WinScene_L,
    GgScene_L,
    Ch1c_L,
    Lscene_L,
    Hero1info_L,
    Ch2c_L,
    Hero2info_L,
} SceneType;
void create_scene(SceneType);

#endif