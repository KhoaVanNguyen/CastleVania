

#include "SceneEndGame.h"

#define BACKGROUND_FILE "Resources/gameover.png"

void SceneEndGame::_initialize()
{
	_localTime = 0;
	_currentSelection = 0;
	_menuOption = (char**)malloc(2 * sizeof(char*));
	_menuOption[0] = "CONTINUE";
	_menuOption[1] = "EXIT";
}

void SceneEndGame::_draw()
{
	switch (_currentSelection)
	{
	case 0:
		_bigFont->renderAnimation(_menuOption[0], 180, 272, 15);
		_smallFont->render(_menuOption[1], 245, 313);
		break;
	case 1:
		_smallFont->render(_menuOption[0], 215, 287);
		_bigFont->renderAnimation(_menuOption[1], 225, 305, 15);
		break;
		
	default:
		break;
	}
}

void SceneEndGame::_openOption()
{
	switch (_currentSelection)
	{
	case 0:
		sceneState = ESceneState::Scene_Game;
		break;
	case 1:
		PostMessage(G_hWnd, WM_QUIT, 0, 0);
		break;
	default:
		break;
	}
}

SceneEndGame::SceneEndGame(void) : Scene(ESceneState::Scene_Menu)
{
	_initialize();
}

void SceneEndGame::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	d3ddv->StretchRect(
		Background,			// from 
		NULL,				// which portion?
		G_BackBuffer,		// to 
		NULL,				// which portion?
		D3DTEXF_NONE);
	this->_draw();
}

void SceneEndGame::OnKeyDown(int KeyCode)
{
	int pre = 0;
	int next = 0;
	switch (KeyCode)
	{
	case DIK_UP:

		_currentSelection = _currentSelection - 1;
		if (_currentSelection < 0) _currentSelection = 1;
		Sound::GetInst()->PlaySoundEffect(ESoundEffect::ES_Select);
		break;
	case DIK_DOWN:
		_currentSelection += 1;
		if (_currentSelection > 1) _currentSelection = 0;
		Sound::GetInst()->PlaySoundEffect(ESoundEffect::ES_Select);
		break;

	case DIK_RETURN:
		this->_openOption();
		break;
	}
}

void SceneEndGame::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	srand((unsigned)time(NULL));

	D3DXCreateSprite(d3ddv, &G_SpriteHandler);


	Background = CreateSurfaceFromFile(d3ddv, BACKGROUND_FILE);
	HRESULT res = D3DXCreateSprite(d3ddv, &G_SpriteHandler);

	_smallFont = new Font(d3ddv, 22, G_ScreenWidth, G_ScreenHeight);
	_bigFont = new Font(d3ddv, 40, G_ScreenWidth, G_ScreenHeight);
}

SceneEndGame::~SceneEndGame(void)
{
}
