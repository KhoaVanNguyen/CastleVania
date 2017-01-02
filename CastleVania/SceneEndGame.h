
#include "Scene.h"
#include "Font.h"
#include "Sound.h"

#define MENU_ANIMATE_STATE 5
#define MENU_MAX_OPTION 3

class SceneEndGame : public Scene
{
protected:
	DWORD _localTime;
	Font* _smallFont;
	Font* _bigFont;
	int _currentSelection;
	char** _menuOption;
	void _initialize();
	void _draw();
	void _openOption();
public:
	SceneEndGame(void);
	void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t);
	void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	void OnKeyDown(int KeyCode);
	~SceneEndGame(void);
};