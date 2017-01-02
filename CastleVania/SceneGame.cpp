#include "SceneGame.h"

#define BACKGROUND_FILE "Resources/black.png"
#define CAMERA_MOVE_SPEED 4
SceneGame::SceneGame(void) : Scene(ESceneState::Scene_Game)
{
	_levelNow = 1;
	_stageNow = 6;
	camera = new GCamera();
	bg = NULL;
	_stateCamera = EStateCamera::Update_Camera;
	gameUI = NULL;
	score = 0;
	totalResets = 3;
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
		camera->viewport.y = 1637; //  485; // 485 - stage 6: 1637
		bg = new BackgroundController(level);
		bg->LoadQuadTreeFromFile();
		player = new Player(345, 1310); //-> Stage 6
		//player = new Player(287, 1310);

		//player = new Player(3776, 96); // stage 1
		_stageReset = 1;
		gameUI = new GameUI(G_Device, 22, G_ScreenWidth, G_ScreenHeight);
		gameUI->initTimer(100);
		Sound::GetInst()->RemoveAllBGM();
		Sound::GetInst()->PlayBGSound(EBGSound::ESoundLevel2);
	}
	break;
	case 2:
	{
		camera->viewport.y = 485; //1253; // 869; // 485

	
		bg = new BackgroundController(level);
		bg->LoadQuadTreeFromFile();
		player = new Player(400, 94);
		//player->posX = 600;
		//player->posY = 140;
		//stage 9 :
		//player = new Player(2403, 606);

		//stage 11 5855 //4420
		//player = new Player(5855, 1040);
		_stageReset = 7;
		player->Initialize();
		//player->hp = 20;
		//player->hearts = 50;
		gameUI = new GameUI(G_Device, 22, G_ScreenWidth, G_ScreenHeight);
		gameUI->initTimer(100);
		Sound::GetInst()->RemoveAllBGM();
		Sound::GetInst()->PlayBGSound(EBGSound::ESoundLevel1);
	}

	break;
	default:
		break;
	}
	posStageToReset.x = player->posX;
	posStageToReset.y = player->posY;
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
			//if (!_firstMoveCameraDone && !_beginMoveCamera && _secondMoveCameraDone)
			//{
			//	player->Stop();
			//	player->_allowPress = true;
			//}
			if (_beginMoveCamera)
			{
				qGameObject->RemoveAllObject();
				MoveCamera(_rangeMoveCamera);
			}
			if (_firstMoveCameraDone)
			{
				if (openDoor->GetOpenDoor())
					openDoor->RenderOpen();
				if (openDoor->GetOpenDoor() == false)
				{
					player->AutoMove(_rangeMovePlayer, t);
					if (_rangeMovePlayer == 0)
					{
						player->SetDirectDoor(EDirectDoor::NoneDoor);
						openDoor->RenderClose();

						//player->_allowPress = false;// lúc đang đóng cửa player không hoạt động
						if (openDoor->GetCloseDoor() == false)
						{
							MoveCamera(_rangeMoveCamera2);
						}
						else
						{
							//if (!_firstMoveCameraDone)
							//{
							//	player->Stop();
							//	player->_allowPress = true;
							//}
							player->_allowPress = true;
						}
					}
				}
			}
#pragma endregion 
		}
//#pragma region Xử lý khi Player die
		// hết máu nhưng chưa thực hiện cái chết :))
		if (player->hp <= 0 && !player->_isDie)
		{
			resetTime = 100;
			player->_isDie = true;
		}
		// đã chết, trở về chỗ hồi sinh
		if (player->_isDie)
		{
				player->_isDie = false;
				player = new Player(posStageToReset.x, posStageToReset.y);
				if (gameUI->getTimer() <= 0)
				{
					if (_levelNow == 1)
						gameUI->initTimer(200);
					else gameUI->initTimer(300);
				}
				LoadStage(_stageReset);
				camera->viewport = posCamera;
				_stageNow = _stageReset;
				totalResets--;
				if (totalResets <= 0)
				{
					sceneState = ESceneState::Scene_Menu;
				}
				else
				{
					if (_stageNow <= 6) // LEVEL1
					{
						// SOUND
						//SoundManager::GetInst()->RemoveAllBGM();
						//SoundManager::GetInst()->PlayBGSound(EBGSound::EStage1Sound);
					}
					else if (_stageNow >= 7) // LEVEL2
					{
						// SOUND
						//SoundManager::GetInst()->RemoveAllBGM();
						//SoundManager::GetInst()->PlayBGSound(EBGSound::EStage2Sound);
					}
				}
			
			
		}
#pragma endregion 
#pragma region nhan MagicalBall de qua man

		if (player->_hasMagicalBall)
		{
			if (player->hp <= 40)
			{
				player->hp++;
			}
			else if (gameUI->getTimer() > 0)
			{
				gameUI->SetTimer(-1000);
				score += 50;
				//SoundManager::GetInst()->PlaySoundEffect(ESoundEffect::ES_GetScoreTimer);
			}
			else if (player->hearts > 0)
			{
				player->hearts--;
				//_score += 100;
				//SoundManager::GetInst()->PlaySoundEffect(ESoundEffect::ES_GetScoreWeaponCount);
			}
			else if (_levelNow == 1)
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
		}
#pragma endregion 


		if (player->_usingStopWatch) {
			qGameObject->PauseUpdate();
			player->_usingStopWatch = false;
			player->hearts -= 6;
		}
	

		//qGameObject->Update(player->GetBox(), t);
	//	qGameObject->Update(t);

		qGameObject->Update(player->posX, player->posY, t);
		bg->GetAvailableTiles(camera->viewport.x, camera->viewport.y);

		player->Update(t);

		if (_stageNow == 6)
		{
			_medusa->Update(t, player->getPos());
			gameUI->updateScore(_stageNow, player->point, t, (int)((player->hp + 1) / 2), player->hearts, totalResets, player->_weaponID,90
				, player->posX, player->posY, (int)camera->viewport.x, (int)camera->viewport.y, player->currentCollideWithID, _secondMoveCameraDone, player->vY, player->abc, player->vX);
			if (_medusa->type == ObjectType::Enemy_Type)
			{
				camera->SetSizeMap(G_RightCamera, G_LeftCamera);
			}
		}
		player->Collision(*(qGameObject->_staticObject), t);
		player->Collision(*(qGameObject->_dynamicObject), t);
		if (player->_usingCross) // player->GetCrossStatus()  )//player->GetUsingCross())
		{

			score += qGameObject->RemoveAllObjectInCamera(camera->viewport);
			//player->SetUsingCross(false);
			//player->CollideWithCrossItem(false);

			player->_usingCross = false;
			// Background
			d3ddv->StretchRect(
				BackgroundWhite,			// from 
				NULL,				// which portion?
				G_BackBuffer,		// to 
				NULL,				// which portion?
				D3DTEXF_NONE);
		}
		else {

			d3ddv->StretchRect(
				Background,
				NULL,
				G_BackBuffer,
				NULL,
				D3DTEXF_NONE);
		}
		qGameObject->Collision(t);
		G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		bg->Draw(camera);
		qGameObject->Draw(camera);
		openDoor->Draw(camera, _doorDirect,_stageNow);
		//gameUI->updateScore(_stageNow, player->point, t, player->hp, player->hearts, 5, player->_weaponID, 5, player->posX, player->posY, (int)camera->viewport.x, (int)camera->viewport.y, player->currentCollideWithID, player->_colStair, player->rangeStair, player->_onStair);
		gameUI->updateScore(_stageNow, player->point, t,(int)(( player->hp+1)/ 2), player->hearts, totalResets, player->_weaponID, 0, player->posX, player->posY, (int)camera->viewport.x, (int)camera->viewport.y, player->currentCollideWithID, _secondMoveCameraDone, player->vY, player->abc, player->vX);
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
		posDoor = qGameObject->GetPosDoor();
	}
	break;
	case 3:
	{
		qGameObject = new QGameObject("Resources/Maps/Stage3.txt");
		posDoor = qGameObject->GetPosDoor();
	}
	break;

	case 4:
	{
		qGameObject = new QGameObject("Resources/Maps/Stage4.txt");
		posDoor = qGameObject->GetPosDoor();

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
		posDoor = qGameObject->GetPosDoor();

	}
	break;
	case 8:
	{
		qGameObject = new QGameObject("Resources/Maps/Stage8.txt");
		posDoor = qGameObject->GetPosDoor();
	}
	break;
	case 9:
	{
		qGameObject = new QGameObject("Resources/Maps/Stage9.txt");
		posDoor = qGameObject->GetPosDoor();
	}
	break;
	case 10:
	{
		qGameObject = new QGameObject("Resources/Maps/Stage10.txt");
		posDoor = qGameObject->GetPosDoor();

	}
	break;
	case 11:
	{
		qGameObject = new QGameObject("Resources/Maps/Stage11.txt");
		posDoor = qGameObject->GetPosDoor();

	}
	break;
	default:
		break;
	}
	camera->SetSizeMap(G_RightCamera, G_LeftCamera);
	openDoor = new OpenDoor(posDoor.x, posDoor.y);
	//openDoor = new OpenDoor(posDoor.x, posDoor.y);
}


void SceneGame::ChangeCamera(EDirectDoor _directDoor)
{

	if (_directDoor != EDirectDoor::NoneDoor)
	{
		switch (_directDoor)
		{
		case TeleDown:
		{
			camera->viewport.y -= (32 * 12); //do cao 1 stage = 32pixcel * 12 dong
			player->posY -= 32;
			player->SetDirectDoor(EDirectDoor::NoneDoor);

			if (_stageNow >= 1) {
				_stageNow--;
				LoadStage(_stageNow);
			}
		}
		break;
		case TeleUp:
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
			_firstMoveCameraDone = false;
			_secondMoveCameraDone = false;
			_rangeMoveCamera = -264;//-264;
			_rangeMoveCamera2 = -264;
			_rangeMovePlayer = -120; // -120;
			_doorDirect = -1;
		}
		break;
		case DoorRight:
		{
			_stateCamera = EStateCamera::NoUpdate_Camera;
			_beginMoveCamera = true;
			_firstMoveCameraDone = false;
			_secondMoveCameraDone = false;
			_rangeMoveCamera = 264;
			_rangeMoveCamera2 = 264;
			_rangeMovePlayer = 120;
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
	if (_rangeMoveCamera == 0)
		_rangeMoveCamera = _moveRange;
	if (_beginMoveCamera)
	{
		player->Stop();
		if (_rangeMoveCamera == 0 && !_firstMoveCameraDone)
		{
			_firstMoveCameraDone = true;
			_beginMoveCamera = false;
			return;
		}
		// qua phải
		if (_rangeMoveCamera > 0)
		{
			_rangeMoveCamera -= CAMERA_MOVE_SPEED;
			camera->viewport.x += CAMERA_MOVE_SPEED;
		}
		// qua trái
		else
		{
			_rangeMoveCamera += CAMERA_MOVE_SPEED;
			camera->viewport.x -= CAMERA_MOVE_SPEED;
		}
	}
	else if (_firstMoveCameraDone)
	{
		player->Stop();
		if (_rangeMoveCamera2 == 0 && !_secondMoveCameraDone)
		{
			_firstMoveCameraDone = false;
			_beginMoveCamera = false;
			_secondMoveCameraDone = true;
			_stageNow++;
			
			LoadStage(_stageNow);
			_stateCamera = EStateCamera::Update_Camera;
			player->SetDirectDoor(EDirectDoor::NoneDoor);
			openDoor->ResetDoor();
			//---------Luu vi tri stage moi de hoi sinh -----------------
			_stageReset = _stageNow;
			posStageToReset.x = player->posX;
			posStageToReset.y = player->posY;
			posCamera = camera->viewport;
			//-----------------------------
			return;
		}
		if (_rangeMoveCamera2 > 0)
		{
			_rangeMoveCamera2 -= CAMERA_MOVE_SPEED;
			camera->viewport.x += CAMERA_MOVE_SPEED;
		}
		else
		{
			_rangeMoveCamera2 += CAMERA_MOVE_SPEED;
			camera->viewport.x -= CAMERA_MOVE_SPEED;
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
	case DIK_W:
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
		break;
	case DIK_M:
		player->ChangeWeapon(EnumID::Throw_Axe_ID);
		break;
	case DIK_N:
		player->ChangeWeapon(EnumID::Boomerang_ID);
		break;
	case DIK_B:
		player->ChangeWeapon(EnumID::Dagger_ID);
		break;
	case DIK_V:
		player->ChangeWeapon(EnumID::StopWatch_ID);
		break;
	case DIK_C:
		player->ChangeWeapon(EnumID::HolyWater_ID);
		break;
	}

}