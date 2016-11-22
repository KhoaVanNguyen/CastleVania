#ifndef _SCENE1_H_
#define _SCENE1_H_

#include "HeaderObj.h"
#include "QBackground.h"
#include "Player.h"
#include "Scene.h"
using namespace std;

class SceneGame : public Scene
{
public:

	SceneGame();
	~SceneGame();
protected:

	LPDIRECT3DSURFACE9 BackgroundWhite;
	D3DXVECTOR2 posCamera;
	QBackground *bg;
	/*QGameObject* qGameObject;*/
	
	GameObject* intro;
	GCamera *camera;
	Player* player;
	ECameraState _cameraState;
	bool _beginMoveCamera;

	void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t);
	void ProcessInput(int keyCode);
	void LoadResources(LPDIRECT3DDEVICE9 d3ddv);

	void OnKeyDown(int KeyCode);
};
#endif
