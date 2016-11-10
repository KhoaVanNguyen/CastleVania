#include "SceneGame.h"

#define BACKGROUND_FILE "Resources/black.png"
#define BACKGROUND_WHITE_FILE "Resources/white.png"
SceneGame::SceneGame(void) : Scene(ESceneState::Scene_Game)
{
	camera = new GCamera();
	bg = NULL;
	if (Background != NULL){
		delete Background;
	}
}


SceneGame::~SceneGame()
{

}
void SceneGame::LoadResources(LPDIRECT3DDEVICE9 d3ddv) {
	srand((unsigned)time(NULL));

	D3DXCreateSprite(d3ddv, &G_SpriteHandler);
	
	Background = CreateSurfaceFromFile(d3ddv, BACKGROUND_FILE);
	BackgroundWhite = CreateSurfaceFromFile(d3ddv, BACKGROUND_WHITE_FILE);
	HRESULT res = D3DXCreateSprite(d3ddv, &G_SpriteHandler);
	
	if (bg != NULL)
		delete bg;

	camera->viewport.y = 450;
	bg = new QBackground(1);
	bg->LoadTree();
	//camera->SetSizeMap(G_MaxSize, G_MinSize);
	
	

}
void SceneGame::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t) {
	d3ddv->StretchRect(
		Background,			// from 
		NULL,				// which portion?
		G_BackBuffer,		// to 
		NULL,				// which portion?
		D3DTEXF_NONE);
	G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	bg->GetTreeObject(500, camera->viewport.y);
	bg->Draw(camera);
	G_SpriteHandler->End();
}

void SceneGame::ProcessInput(int KeyCode) {

}

void SceneGame::OnKeyDown(int KeyCode) {

}