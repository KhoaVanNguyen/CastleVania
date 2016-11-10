#ifndef _SCENECONTROL_H_
#define _SCENECONTROL_H_

#include "Game.h"
#include "CEnum.h"
#include "Scene.h"
#include "SceneMenu.h"
#include "SceneGame.h"
class SceneControl: public CGame
{
public: 	
	SceneControl(int _nCmdShow);
	~SceneControl();	
	Scene *sceneNow;
	ESceneState currentStateScene;
protected:	

	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);

	virtual void OnKeyDown(int KeyCode);
};

#endif