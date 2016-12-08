#include "SceneGame.h"

#define BACKGROUND_FILE "Resources/black.png"
SceneGame::SceneGame(void) : Scene(ESceneState::Scene_Game)
{
	_levelNow = 1;
	_stageNow = 1;
	camera = new GCamera();
	bg = NULL;
	_cameraState = ECameraState::Update;
	gameUI = NULL;
}

SceneGame::~SceneGame()
{

}
void SceneGame::LoadResources(LPDIRECT3DDEVICE9 d3ddv) {
	srand((unsigned)time(NULL));

	D3DXCreateSprite(d3ddv, &G_SpriteHandler);
	
	Background = CreateSurfaceFromFile(d3ddv, BACKGROUND_FILE);
	HRESULT res = D3DXCreateSprite(d3ddv, &G_SpriteHandler);
	
	if (bg != NULL)
		delete bg;

	LoadLevel(_levelNow);

	LoadStage(_stageNow);

}void SceneGame::LoadLevel(int level)
{
	//ResetLevel();
	if (qGameObject != NULL)
		delete qGameObject;
	switch (level)
	{
	
	case 1:
	{
		camera->viewport.y = 482;
		bg = new QBackground(level);
		bg->LoadTree();
		player = new Player(3700,96);
		//player->posX = 3776;
		//player->posY = 96;
		gameUI = new GameUI(G_Device, 22, G_ScreenWidth, G_ScreenHeight);
		gameUI->initTimer(100);

	}
	break;
	default:
		break;
	}
	//posStageToReset.x = simon->posX;
	//posStageToReset.y = simon->posY;
	posCamera = camera->viewport;
}
void SceneGame::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t) {
	qGameObject->Update(t);
	bg->GetTreeObject(camera->viewport.x, camera->viewport.y);
	
	player->Update(t);

	if (_cameraState== ECameraState::Update)
	{
		camera->UpdateCamera(player->posX);
	}

	player->Collision(*(qGameObject->_staticObject), t);
	player->Collision(*(qGameObject->_dynamicObject), t);


	qGameObject->Collision(t);
	d3ddv->StretchRect(
		Background,	
		NULL,	
		G_BackBuffer,
		NULL,	
		D3DTEXF_NONE);
	G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	bg->Draw(camera);
	qGameObject->Draw(camera);

	
	//gameUI->updateScore(1, player->point, t, 10, 1, 5, 5);
	//gameUI->drawTable();
	
	gameUI->updateScore(1, player->point, t, player->hp, player->hearts, 5, 5);
	gameUI->drawTable();
	player->Draw(camera);

	G_SpriteHandler->End();

	gameUI->drawScore();
}

void SceneGame::LoadStage(int stage)
{
	switch (stage)
	{
	case 1:
	{
		qGameObject = new QGameObject("Resources/Maps/Stage1.txt");
		
	}
	break;

	case 2:
	{
		qGameObject = new QGameObject("Resources/Maps/Stage2.txt");

	}
	break;
	case 3:
	{
		qGameObject = new QGameObject("Resources/Maps/Stage3.txt");

	}
	break;

	case 4:
	{
		qGameObject = new QGameObject("Resources/Maps/Stage4.txt");
		//posDoor = qGameObject->GetPosDoor();
//		_phantomBat = qGameObject->getPhantomBat();
		
	}

	break;
	case 5:
	{
		qGameObject = new QGameObject("Resources/Maps/Stage5.txt");
		//posDoor = qGameObject->GetPosDoor();

	}
	break;
	case 6:
	{
		qGameObject = new QGameObject("Resources/Maps/Stage6.txt");
		//posDoor = qGameObject->GetPosDoor();

	}
	break;
	case 7:
	{
		qGameObject = new QGameObject("Resources/Maps/Stage7.txt");
		//posDoor = qGameObject->GetPosDoor();

	}
	break;
	case 8:
	{
		qGameObject = new QGameObject("Resources/Maps/Stage8.txt");
		//posDoor = qGameObject->GetPosDoor();

	}
	break;
	case 9:
	{
		qGameObject = new QGameObject("Resources/Maps/Stage9.txt");
		//posDoor = qGameObject->GetPosDoor();
	}
	break;
	case 10:
	{
		qGameObject = new QGameObject("Resources/Maps/Stage10.txt");
		//posDoor = qGameObject->GetPosDoor();
		//_Medusa = qGameObject->getMedusa();

	}
	break;
	default:
		break;
	}
	camera->SetSizeMap(G_MaxSize, G_MinSize);
	//openDoor = new OpenDoor(posDoor.x, posDoor.y);
}

void SceneGame::ProcessInput(int KeyCode) {

	switch (KeyCode)
	{

	
	case DIK_RIGHT:
		player->TurnRight();
	case DIK_D:
		player->TurnRight();
		break;
	case DIK_LEFT:
		player->TurnLeft();
	case DIK_A:
		player->TurnLeft();
		break;
	case DIK_DOWN:
	case DIK_S:
		if (player->OnStair())
		{
			player->DownStair();
		}
		else
			player->Sit();
		break;
	case DIK_Q:
		player->UseWeapon();
		break;
	case DIK_UP:
		player->UpStair();
		break;
	default:
		player->Stop();
		break;
	}
}
	

void SceneGame::OnKeyDown(int KeyCode) {
	switch (KeyCode)
	{
	case DIK_RETURN:
		player->Fight();
		break;
	case DIK_SPACE:
		player->Jump();
	case DIK_M:
		player->ChangeWeapon(EnumID::Throw_Axe);
		break;
	}
	
}