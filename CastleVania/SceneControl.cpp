
#include "SceneControl.h"
SceneControl::SceneControl(int _nCmdShow): CGame(_nCmdShow)
{
	sceneNow = new SceneMenu();
	currentStateScene = ESceneState::Scene_Menu;

}

void SceneControl::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t)
{


	if (sceneNow->sceneState != currentStateScene)
	{
		switch (sceneNow->sceneState)
		{
		
		case ESceneState::Scene_Menu:
			sceneNow = new SceneMenu();
			sceneNow->LoadResources(d3ddv);
			break;
		case ESceneState::Scene_Game:
			sceneNow = new SceneGame();
			sceneNow->LoadResources(d3ddv);
			break;
		}
		currentStateScene = sceneNow->sceneState;
	}
	sceneNow->RenderFrame(d3ddv, t);
}

void SceneControl::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta)
{
}

void SceneControl::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	sceneNow->LoadResources(d3ddv);
}

void SceneControl::OnKeyDown(int KeyCode)
{
	sceneNow->OnKeyDown(KeyCode);
}

SceneControl::~SceneControl(void)
{
}
