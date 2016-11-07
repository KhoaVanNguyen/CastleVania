#include "SceneGame.h"

#define BACKGROUND_FILE "Resources/black.png"

SceneGame::SceneGame(void) : Scene(ESceneState::Scene_Game)
{
	camera = new GCamera();
	bg = NULL;
}


SceneGame::~SceneGame()
{

}
void SceneGame::LoadResources(LPDIRECT3DDEVICE9 d3ddv) {
	srand((unsigned)time(NULL));

	D3DXCreateSprite(d3ddv, &G_SpriteHandler);

	Background = CreateSurfaceFromFile(d3ddv, BACKGROUND_FILE);
	HRESULT res = D3DXCreateSprite(d3ddv, &G_SpriteHandler);
	camera->viewport.y = 450;
	bg = new QBackground(1);
	bg->LoadTree();

}
void SceneGame::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t) {

}

void SceneGame::ProcessInput(int KeyCode) {

}

void SceneGame::OnKeyDown(int KeyCode) {

}