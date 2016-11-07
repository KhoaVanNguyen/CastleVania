#include "Scene.h"


Scene::Scene(ESceneState state)
{
	Background = NULL;
	camera = NULL;
	sceneState = state;
}

void Scene::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t)
{
}

void Scene::ProcessInput(int keycode)
{
}

ESceneState Scene::GetSceneState()
{
	return sceneState;
}

void Scene::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
}

void Scene::OnKeyDown(int KeyCode)
{
}

Scene::~Scene(void)
{
}
