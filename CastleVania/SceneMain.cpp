
#include "SceneMain.h"

SceneMain::SceneMain(int _nCmdShow): CGame(_nCmdShow)
{
	sceneNow = new SceneMenu();
	currentStateScene = ESceneState::Scene_Menu;

}

void SceneMain::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t)
{


	if (sceneNow->sceneState != currentStateScene)
	{
		switch (sceneNow->sceneState)
		{
		
		case ESceneState::Scene_Menu:
			sceneNow = new SceneMenu();
			sceneNow->LoadResources(d3ddv);
			break;
		}
		currentStateScene = sceneNow->sceneState;
	}
	sceneNow->RenderFrame(d3ddv, t);
}

void SceneMain::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta)
{
}

void SceneMain::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	sceneNow->LoadResources(d3ddv);
}

void SceneMain::OnKeyDown(int KeyCode)
{
	sceneNow->OnKeyDown(KeyCode);
}

SceneMain::~SceneMain(void)
{
}
