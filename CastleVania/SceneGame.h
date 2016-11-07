#ifndef _SCENEGAME_H_
#define _SCENEGAME_H_
#include "Scene.h"
class SceneGame : public Scene
{
public:
	SceneGame();
	~SceneGame();


	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t);
	virtual void ProcessInput(int keyCode);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	virtual void OnKeyDown(int KeyCode);
};

#endif