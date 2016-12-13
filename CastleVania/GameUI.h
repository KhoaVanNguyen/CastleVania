#pragma once
#include "GSprite.h"
#include "Singleton.h"
#include "Font.h"
#include <vector>
using namespace std;

#define MAX_HP 20

class GameUI
{
protected:
	GSprite* _sprite;
	Font* _arial;
	int _playerScore;
	int _gameTimer;
	int _gameStage;
	int _weaponCount;
	int _playerHP;
	int _enemyHP;
	int _liveCount;
	int _currentWeapon;
	vector<GSprite*> weapons;
	GSprite* _hpSprite;
	void _initialize();


public:
	GameUI(void);
	GameUI(LPDIRECT3DDEVICE9 d3ddev_, int size_, int screenWidth_, int screenHeight_);
	void drawTable();
	void drawScore();
	// deltaTime is in second
	void initTimer(int deltaTime_);
	int getTimer(); // return Time left of game in second
	void SetTimer(int x);
	int GetWeaponCount();
	void SetWeaponCount(int x);
	void SetSimonScore(int x);
	// deltaTime_ is in milisecond
	void updateScore(int gameStage_, int simonScore_, int deltaTime_, int simonHP_, int liveCount_, int weaponCount_, EnumID weaponID_, int enemyHP_ = 20);
	~GameUI(void);
};

