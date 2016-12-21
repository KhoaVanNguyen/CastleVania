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

	int _playerX;
	int _playerY;
	int _viewPortY;
	int _viewPortX;

	int _collideID;
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
	void SetplayerScore(int x);
	// deltaTime_ is in milisecond
	void updateScore(int gameStage_, int playerScore_, int deltaTime_, int playerHP_, int liveCount_, int weaponCount_, EnumID weaponID_, int enemyHP_ = 20);
	
	void updateScore(int gameStage_, int playerScore_, int deltaTime_, int playerHP_, int liveCount_, int weaponCount_, EnumID weaponID_, int enemyHP_, int _x, int _y,int viewPortX, int viewPortY);
	
	void updateScore(int gameStage_, int playerScore_, int deltaTime_, int playerHP_, int liveCount_, int weaponCount_, EnumID weaponID_, int enemyHP_, int _x, int _y, int viewPortX, int viewPortY, int collideId);
	~GameUI(void);
};

