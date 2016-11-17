#include "SceneGame.h"

#define BACKGROUND_FILE "Resources/black.png"
SceneGame::SceneGame(void) : Scene(ESceneState::Scene_Game)
{
	camera = new GCamera();
	bg = NULL;
	_cameraState = ECameraState::Update;
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

	camera->viewport.y = 450;
	bg = new QBackground(1);
	bg->LoadTree(); 
	player = new Player(50, 64);

	//qGameObject = new QGameObject("Resources/Maps/Stage1.txt");
	camera->SetSizeMap(1520,16);
	
}
void SceneGame::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t) {

	bg->GetTreeObject(camera->viewport.x, camera->viewport.y);
	player->Update(t);

	if (_cameraState== ECameraState::Update)
	{
		camera->UpdateCamera(player->posX);
	}


	d3ddv->StretchRect(
		Background,			// from 
		NULL,				// which portion?
		G_BackBuffer,		// to 
		NULL,				// which portion?
		D3DTEXF_NONE);
	G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	bg->Draw(camera);
	player->Draw(camera);
	G_SpriteHandler->End();
}

void SceneGame::ProcessInput(int KeyCode) {
	
	switch (KeyCode)
	{
	case DIK_RIGHT:
		
		player->TurnRight();
		break;
	case DIK_D:
		player->TurnRight();
		break;
	case DIK_LEFT:
		player->TurnLeft();
		break;
	case DIK_A:
		player->TurnLeft();
		break;
	case DIK_J:
		player->Jump();
		break;
	//case DIK_DOWN:
	case DIK_S:
		player->Sit();
		break;
	
	}
}
	

void SceneGame::OnKeyDown(int KeyCode) {

}
