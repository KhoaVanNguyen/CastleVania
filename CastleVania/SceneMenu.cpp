

#include "SceneMenu.h"

#define BACKGROUND_FILE "Resources/mainmenu.png"

void SceneMenu::_initialize()
{
	_localTime = 0;
	_currentSelection = 0;
	_menuOption = (char**)malloc(3 * sizeof(char*));
	_menuOption[0] = "PLAY";
	_menuOption[1] = "CONTINUE";
	_menuOption[2] = "EXIT";
}

void SceneMenu::_draw()
{
	switch (_currentSelection)
	{
	case 0:
		_bigFont->renderAnimation(_menuOption[0], 220, 252, 15);
		_smallFont->render(_menuOption[1], 215, 293);
		_smallFont->render(_menuOption[2], 243, 320);
		break;
	case 1:
		_smallFont->render(_menuOption[0], 240, 267);
		_bigFont->renderAnimation(_menuOption[1], 180, 285, 15);
		_smallFont->render(_menuOption[2], 243, 320);
		break;
	case 2:
		_smallFont->render(_menuOption[0], 240, 267);
		_smallFont->render(_menuOption[1], 215, 293);
		_bigFont->renderAnimation(_menuOption[2], 230, 315, 15);
		break;
	default:
		break;
	}
}

void SceneMenu::_openOption()
{
	switch (_currentSelection)
	{
	case 0:
		sceneState = ESceneState::Scene_Game;
		break;
	case 1:
		sceneState = ESceneState::Scene_Game;
		break;
	case 2:
		PostMessage(G_hWnd, WM_QUIT, 0, 0);
		break;
	default:
		break;
	}
}

SceneMenu::SceneMenu(void) : Scene(ESceneState::Scene_Menu)
{
	_initialize();
}

void SceneMenu::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	d3ddv->StretchRect(
		Background,			// from 
		NULL,				// which portion?
		G_BackBuffer,		// to 
		NULL,				// which portion?
		D3DTEXF_NONE);
	this->_draw();
}

void SceneMenu::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_UP:
		_currentSelection = (_currentSelection - 1) % MENU_MAX_OPTION;
		if (_currentSelection<0)
			_currentSelection += 3;
		//SoundManager::GetInst()->PlaySoundEffect(ESoundEffect::ES_Select);
		break;
	case DIK_DOWN:
		_currentSelection = (_currentSelection + 1) % MENU_MAX_OPTION;
		//SoundManager::GetInst()->PlaySoundEffect(ESoundEffect::ES_Select);
		break;
	case DIK_RETURN:
		this->_openOption();
		break;
	}
}

void SceneMenu::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	srand((unsigned)time(NULL));

	D3DXCreateSprite(d3ddv, &G_SpriteHandler);

	Background = CreateSurfaceFromFile(d3ddv, BACKGROUND_FILE);

	HRESULT res = D3DXCreateSprite(d3ddv, &G_SpriteHandler);

	_smallFont = new Font(d3ddv, 22, G_ScreenWidth, G_ScreenHeight);
	_bigFont = new Font(d3ddv, 40, G_ScreenWidth, G_ScreenHeight);

	//SoundManager::GetInst()->RemoveAllBGM();
	//SoundManager::GetInst()->PlayBGSound(EBGSound::EMenuSound);
}

SceneMenu::~SceneMenu(void)
{
}
