#include "SceneGame.h"

#define BACKGROUND_FILE "Resources/black.png"
SceneGame::SceneGame(void) : Scene(ESceneState::Scene_Game)
{
	_levelNow = 1;
	_stageNow = 1;
	camera = new GCamera();
	bg = NULL;
	_stateCamera = EStateCamera::Update_Camera;
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
		camera->viewport.y = 485; // 485
		bg = new QBackground(level);
		bg->LoadTree();
		player = new Player(3776, 96);
		//player = new Player(287, 1310);
		//player->posX = 3776;
		//player->posY = 96;
		gameUI = new GameUI(G_Device, 22, G_ScreenWidth, G_ScreenHeight);
		gameUI->initTimer(100);
		/*Sound::GetInst()->RemoveAllBGM();
		Sound::GetInst()->PlayBGSound(EBGSound::EStage1Sound);*/

	}
	break;
	case 2:
	{

		camera->viewport.y = 485; // 485
		bg = new QBackground(level);
		bg->LoadTree();
		//player = new Player(600, 90);
		player->posX = 600;
		player->posY = 140;
		gameUI = new GameUI(G_Device, 22, G_ScreenWidth, G_ScreenHeight);
		gameUI->initTimer(100);
		/*Sound::GetInst()->RemoveAllBGM();
		Sound::GetInst()->PlayBGSound(EBGSound::EStage1Sound);*/

	}
	
	break;
	default:
		break;
	}
	
	posCamera = camera->viewport;
}
void SceneGame::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t) {

	if (_levelNow == 0)
	{
		// Load intro game ở dây
	}
	else if (_levelNow > 0)
	{

		if (_stateCamera == EStateCamera::Update_Camera)
		{
			camera->UpdateCamera(player->posX);
			ChangeCamera(player->GetDirectDoor());
		}
		else {
#pragma region Chuyen canh, dich chuyen camera

			if (_beginMoveCamera)
			{
				qGameObject->RemoveAllObject();
				MoveCamera(_rangeMoveCamera);
			}
			if (_moveCameraHaft)
			{
				if (openDoor->GetOpenDoor())
					openDoor->RenderOpen();
				if (openDoor->GetOpenDoor() == false)
				{
					player->AutoMove(_rangeMoveplayer, t);
					if (_rangeMoveplayer == 0)
					{
						player->SetDirectDoor(EDirectDoor::NoneDoor);
						openDoor->RenderClose();
						if (openDoor->GetCloseDoor() == false)
						{
							MoveCamera(_rangeMoveCamera2);
						}
						else
						{
							player->_allowPress = true;

						}
					}
				}
			}
#pragma endregion 
		}

#pragma region nhan duoc MagicalBall qua man
		if (player->_hasMagicalBall)
			//{
			//	if (player->GetHPplayer() < 40)
			//	{
			//		player->hp++;
			//	}
			//	else if (_gameScore->getTimer() > 0)
			//	{
			//		_gameScore->SetTimer(-1000);
			//		//_score += 50;
			//		//SoundManager::GetInst()->PlaySoundEffect(ESoundEffect::ES_GetScoreTimer);
			//	}
			//	else if (player->hearts > 0)
			//	{
			//		player->hearts--;
			//		//_score += 100;
			//		//SoundManager::GetInst()->PlaySoundEffect(ESoundEffect::ES_GetScoreWeaponCount);
			//	}
			//	else 
			if (_levelNow == 1  )
			{
				_levelNow++;
				_stageNow++;
				LoadResources(G_Device);
				player->_hasMagicalBall = false;
			}
			else if (_levelNow == 2)
			{
				sceneState = ESceneState::Scene_End;
			}
#pragma endregion 

		qGameObject->Update(t);
		bg->GetTreeObject(camera->viewport.x, camera->viewport.y);

		player->Update(t);

		if (_stageNow == 6)
		{
			_medusa->Update(t, player->getPos());
			//_gameScore->updateScore(_stageNow, _score, deltaTime, (int)((player->hp + 1) / 2), _lifes, player->_weaponID, player->hearts, _queenMedusa->hp);
			if (_medusa->type == ObjectType::Enemy_Type)
			{
				camera->SetSizeMap(G_LeftCamera, G_RightCamera);
			}
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
		openDoor->Draw(camera, _doorDirect);
		gameUI->updateScore(_stageNow, player->point, t, player->hp, player->hearts, 5, player->_weaponID, 5, player->posX, player->posY, (int)camera->viewport.x, (int)camera->viewport.y);
		gameUI->drawTable();
		player->Draw(camera);
		G_SpriteHandler->End();
		gameUI->drawScore();
	}
}



void SceneGame::LoadStage(int stage)
{
	switch (stage)
	{
	case 1:
	{
		qGameObject = new QGameObject("Resources/Maps/Stage1.txt");
		_medusa = qGameObject->getMedusa();
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
		
		
	}

	break;
	case 5:
	{
		qGameObject = new QGameObject("Resources/Maps/Stage5.txt");
		posDoor = qGameObject->GetPosDoor();

	}
	break;
	case 6:
	{
		qGameObject = new QGameObject("Resources/Maps/Stage6.txt");
		posDoor = qGameObject->GetPosDoor();
		_medusa = qGameObject->getMedusa();
	}
	break;
	case 7:
	{
		qGameObject = new QGameObject("Resources/Maps/Stage7.txt");
		

	}
	break;
	case 8:
	{
		qGameObject = new QGameObject("Resources/Maps/Stage8.txt");
		
	}
	break;
	case 9:
	{
		qGameObject = new QGameObject("Resources/Maps/Stage9.txt");
	
	}
	break;
	case 10:
	{
		qGameObject = new QGameObject("Resources/Maps/Stage10.txt");
		

	}
	break;
	default:
		break;
	}
	camera->SetSizeMap(G_LeftCamera, G_RightCamera);
	openDoor = new OpenDoor(posDoor.x, posDoor.y);
}


void SceneGame::ChangeCamera(EDirectDoor _directDoor)
{

	if (_directDoor != EDirectDoor::NoneDoor)
	{
		switch (_directDoor)
		{
		case DoorDown:
		{
			camera->viewport.y -= (32 * 12); //do cao 1 stage = 32pixcel * 12 dong
			player->posY -= 64;
			player->SetDirectDoor(EDirectDoor::NoneDoor);

			if (_stageNow >= 1) {
				_stageNow--;
				LoadStage(_stageNow);
			}
		}
		break;
		case DoorUp:
		{
			camera->viewport.y += (32 * 12); //do cao 1 stage = 32pixcel * 12 dong
			player->posY += 64;
			player->SetDirectDoor(EDirectDoor::NoneDoor);

			_stageNow++;
			LoadStage(_stageNow);
		}
		break;
		case DoorLeft:
		{
			_stateCamera = EStateCamera::NoUpdate_Camera;
			_beginMoveCamera = true;
			_moveCameraHaft = false;
			_moveCameraDone = false;
			_rangeMoveCamera = -264;//-264;
			_rangeMoveCamera2 = -220;
			_rangeMoveplayer = -120; // -120;
			_doorDirect = -1;
		}
		break;
		case DoorRight:
		{
			_stateCamera = EStateCamera::NoUpdate_Camera;
			_beginMoveCamera = true;
			_moveCameraHaft = false;
			_moveCameraDone = false;
			_rangeMoveCamera = 270;
			_rangeMoveCamera2 = 224;
			_rangeMoveplayer = 120;
			_doorDirect = 1;
		}
		break;
		default:
			break;
		}
	}

}

void SceneGame::MoveCamera(int &_moveRange)
{
	if(_rangeMoveCamera == 0)
		_rangeMoveCamera = _moveRange;
	if (_beginMoveCamera)
	{
		if (_rangeMoveCamera == 0 && !_moveCameraHaft)
		{
			_moveCameraHaft = true;
			_beginMoveCamera = false;
			return;
		}
		if (_rangeMoveCamera > 0)
		{
			_rangeMoveCamera -= 4;
			camera->viewport.x += 4;
		}
		else
		{
			_rangeMoveCamera += 4;
			camera->viewport.x -= 4;
		}
	}
	else if (_moveCameraHaft)
	{
		if (_rangeMoveCamera2 == 0 && !_moveCameraDone)
		{
			_moveCameraHaft = false;
			_beginMoveCamera = false;
			_moveCameraDone = true;
			_stageNow++;
			LoadStage(_stageNow);
			_stateCamera = EStateCamera::Update_Camera;
			player->SetDirectDoor(EDirectDoor::NoneDoor);
			openDoor->ResetDoor();
			//---------Luu vi tri stage moi de hoi sinh -----------------
			_stageReset = _stageNow;
			/*posStageToReset.x = player->posX;
			posStageToReset.y = player->posY;*/
			posCamera = camera->viewport;
			//-----------------------------
			return;
		}
		if (_rangeMoveCamera2 > 0)
		{
			_rangeMoveCamera2 -= 4;
			camera->viewport.x += 4;
		}
		else
		{
			_rangeMoveCamera2 += 4;
			camera->viewport.x -= 4;
		}
	}

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
		player->ChangeWeapon(EnumID::Throw_Axe_ID);
		break;
	case DIK_N:
		player->ChangeWeapon(EnumID::Boomerang_ID);
		break;
	case DIK_B:
		player->ChangeWeapon(EnumID::Dagger_ID);
		break;
	}
	
}