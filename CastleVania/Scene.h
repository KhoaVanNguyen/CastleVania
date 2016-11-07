#ifndef _SCENE_H_
#define _SCENE_H_

#include <d3dx9.h>
#include "Utils.h"
#include <time.h>
#include "Global.h"
#include <string>
#include <iostream>
#include <conio.h>
#include <sstream>
#include "GCamera.h"
//#include "SoundManager.h"
#include "CEnum.h"
#include "Game.h"

class Scene
{
public:
	LPDIRECT3DSURFACE9 Background;
	GCamera* camera;
	ESceneState sceneState;

	Scene(ESceneState);
	ESceneState GetSceneState();
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t);
	virtual void ProcessInput(int keyCode);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	virtual void OnKeyDown(int KeyCode);
	~Scene(void);
};

#endif