#include <windows.h>
#include "SceneMain.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SceneMain *game = new SceneMain(nCmdShow);
	game->InitGame();
	game->GameRun();
	game->GameEnd();
	return 0;
}