
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
	if (currentStateScene == ESceneState::Scene_Game)
	{
		if (IsKeyDown(DIK_RIGHT) || IsKeyDown(DIK_D))
		{
			sceneNow->ProcessInput(DIK_RIGHT);
		}
		else if (IsKeyDown(DIK_LEFT) || IsKeyDown(DIK_A))
		{
			sceneNow->ProcessInput(DIK_LEFT);
		}
		else if (IsKeyDown(DIK_DOWN) || IsKeyDown(DIK_S))
		{
			sceneNow->ProcessInput(DIK_DOWN);
		}
		else if (IsKeyDown(DIK_UP) || IsKeyDown(DIK_W))
		{
			sceneNow->ProcessInput(DIK_UP);
		}
		else if (IsKeyDown(DIK_Q))
		{
			sceneNow->ProcessInput(DIK_Q);
		}
		else if (IsKeyDown(DIK_J))
		{
			sceneNow->ProcessInput(DIK_J);
		}
		else
		{
			sceneNow->ProcessInput(DIK_0);
		}
	}
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
