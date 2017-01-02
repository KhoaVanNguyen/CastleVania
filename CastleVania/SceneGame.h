#ifndef _SCENE1_H_
#define _SCENE1_H_

#include "HeaderObj.h"
#include "BackgroundController.h"
#include "Player.h"
#include "Scene.h"
#include "QGameObject.h"
#include "GameUI.h"
#include "Sound.h"
using namespace std;

class SceneGame : public Scene
{
public:

	SceneGame();
	~SceneGame();
protected:
//	PhantomBat* _phantomBat;

	Medusa* _medusa;
	LPDIRECT3DSURFACE9 BackgroundWhite;
	D3DXVECTOR2 posCamera;
	D3DXVECTOR2 posStageToReset; //Vi tri hoi sinh
	D3DXVECTOR2 posDoor;
	BackgroundController *bg;
	QGameObject* qGameObject;


	AxeKnights* knight;
	int _levelNow, _stageNow;
	GCamera *camera;
	Player* player;
	
	bool _beginMoveCamera;

	// Score
	int score;
	// Player die
	bool _playerDie;
	int totalResets;
	int resetTime;
	//camera
	void MoveCamera(int &_moveRange);
	void ChangeCamera(EDirectDoor _directDoor);
	EStateCamera _stateCamera;
	int _rangeMoveCamera;
	int _rangeMoveCamera2;
	int _rangeMovePlayer;
	

	// door open and close
	OpenDoor* openDoor;
	int _stageReset;
	

	bool _firstMoveCameraDone;	//Di chuyen camera lan 1
	bool _secondMoveCameraDone;	//Di chuyen camera lan 2
	int _doorDirect; //Huong mo cua

	GameUI* gameUI;

	void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t);
	void ProcessInput(int keyCode);
	void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	void LoadLevel(int);
	void LoadStage(int);
	void OnKeyDown(int KeyCode);
};
#endif
