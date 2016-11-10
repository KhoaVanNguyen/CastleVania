#include <windows.h>
#include "SceneControl.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SceneControl *game = new SceneControl(nCmdShow);
	game->InitGame();
	game->GameRun();
	game->GameEnd();
	return 0;
}