#include "GameUI.h"


void GameUI::_initialize()
{
	// init weaponSprite
	// _currentWeapon dùng để vẽ hình weapon trên UI thôi
	weapons = vector<GSprite*>();
	weapons.push_back(new GSprite(TextureManager::getInstance()->getTexture(EnumID::Dagger_ID), 1));
	weapons.push_back(new GSprite(TextureManager::getInstance()->getTexture(EnumID::Boomerang_ID), 1));
	weapons.push_back(new GSprite(TextureManager::getInstance()->getTexture(EnumID::Throw_Axe_ID), 1));
	weapons.push_back(new GSprite(TextureManager::getInstance()->getTexture(EnumID::StopWatch_ID), 1));
	weapons.push_back(new GSprite(TextureManager::getInstance()->getTexture(EnumID::HolyWaterItem_ID), 1));

	// init hp sprite
	_hpSprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::HP_ID), 1);

	_gameTimer = 0;
	_enemyHP = 0;
}
GameUI::GameUI(LPDIRECT3DDEVICE9 d3ddev_, int size_, int screenWidth_, int screenHeight_)
{
	this->_initialize();
	_sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::GameUI_ID), 1);
	_arial = new Font(d3ddev_, size_, screenWidth_, screenHeight_);
}
void GameUI::drawTable()
{
	// draw table
	_sprite->Draw(260, 40);

	// draw hp
	for (int i = 0; i<_playerHP; i++)
	{
		_hpSprite->DrawIndex(0, 100 + 10 * i, 30);
	}
	for (int i = _playerHP; i<MAX_HP; i++)
	{
		_hpSprite->DrawIndex(1, 100 + 10 * i, 30);
	}
	// boss
	for (int i = 0; i<_enemyHP; i++)
	{
		_hpSprite->DrawIndex(2, 100 + 10 * i, 50);
	}
	for (int i = _enemyHP; i<MAX_HP; i++)
	{
		_hpSprite->DrawIndex(1, 100 + 10 * i, 50);
	}


	// draw weapon
	if (_currentWeapon != -1)
	{
		weapons.at(_currentWeapon)->Draw(345, 48);
	}

}

void GameUI::drawScore()
{
	_arial->onLost();
	_arial->render("Score", 5, 0);
	_arial->render(_playerScore, 100, 0);
	_arial->render("TIME", 230, 0);
	_arial->render(_gameTimer / 1000, 310, 0);
	_arial->render("STAGE", 400, 0);
	_arial->render(_gameStage, 490, 0);
	_arial->render("PLAYER", 5, 20);
	_arial->render("ENEMY", 5, 40);



	//_arial->render("PASS GAME :))", 5, 60);
	_arial->render("viewport.x: ", 5, 60);
	_arial->render(_viewPortX, 100, 60);

	_arial->render("viewport.y: ", 5, 80);
	_arial->render(_viewPortY, 100, 80);

	_arial->render("X: ", 150, 60);
	_arial->render(_playerX, 170, 60);
	_arial->render("Y: ", 220, 60);
	_arial->render(_playerY, 240, 60);


	_arial->render(_liveCount, 420, 30);
	_arial->render(_weaponCount, 430, 50);

	_arial->render("collide ID: ", 150, 80);
	_arial->render(_collideID, 250, 80);
	_arial->render("colstair: ", 390, 80);
	_arial->render(_colabc, 480, 80);
	_arial->render("ranger: ", 290, 80);
	_arial->render(_rang, 360, 80);
	//_arial->render("onstair: ", 290, 80);
	_arial->render(_onstair, 390, 100);
	_arial->render(_checkCameraHaft, 100, 100);
}

void GameUI::initTimer(int deltaTime_)
{
	_gameTimer = deltaTime_ * 1000;
}

int GameUI::getTimer()
{
	return _gameTimer / 1000;
}

void GameUI::SetTimer(int x)
{
	_gameTimer += x;
}

int GameUI::GetWeaponCount()
{
	return _weaponCount;
}

void GameUI::SetWeaponCount(int x)
{
	_weaponCount += x;
}

void GameUI::SetplayerScore(int x)
{
	_playerScore += x;
}

GameUI::GameUI(void)
{

}




void GameUI::updateScore(int gameStage_, int playerScore_, int deltaTime_, int playerHP_, int liveCount_, int weaponCount_, EnumID weaponID_, int enemyHP_)
{
	//(int gameStage_, int playerScore_, int deltaTime_, int playerHP_, int liveCount_, EnumID weaponID_, int weaponCount_, int enemyHP_)
	_gameStage = gameStage_;
	_playerScore = playerScore_;
	if (_gameTimer <= 0)
	{
	}
	else
		_gameTimer = _gameTimer - deltaTime_;
	_weaponCount = weaponCount_;
	_playerHP = playerHP_;
	_enemyHP = enemyHP_;
	_liveCount = liveCount_;

	switch (weaponID_)
	{

	case Dagger_ID:
		_currentWeapon = 0;
		break;
	case Boomerang_ID:
		_currentWeapon = 1;
		break;
	case Throw_Axe_ID:
		_currentWeapon = 2;
		break;
	case StopWatch_ID:
		_currentWeapon = 3;
		break;
	case HolyWaterItem_ID:
		_currentWeapon = 4;
		break;
	default:
		_currentWeapon = -1;
		break;
	}

}


void GameUI::updateScore(int gameStage_, int playerScore_, int deltaTime_, int playerHP_, int liveCount_, int weaponCount_, EnumID weaponID_, int enemyHP_, int _x, int _y, int viewPortX, int viewPortY)
{
	//(int gameStage_, int playerScore_, int deltaTime_, int playerHP_, int liveCount_, EnumID weaponID_, int weaponCount_, int enemyHP_)
	_gameStage = gameStage_;
	_playerScore = playerScore_;
	if (_gameTimer <= 0)
	{
	}
	else
		_gameTimer = _gameTimer - deltaTime_;
	_weaponCount = weaponCount_;
	_playerHP = playerHP_;
	_enemyHP = enemyHP_;
	_liveCount = liveCount_;
	_playerX = _x;
	_playerY = _y;
	_viewPortY = viewPortY;
	_viewPortX = viewPortX;
	switch (weaponID_)
	{
		/*case Watch_ID:
		_currentWeapon = 0;
		break;*/
	case Dagger_ID:
		_currentWeapon = 0;
		break;
	case Boomerang_ID:
		_currentWeapon = 1;
		break;
	case Throw_Axe_ID:
		_currentWeapon = 2;
		break;
	default:
		_currentWeapon = -1;
		break;
	}

}



void GameUI::updateScore(int gameStage_, int playerScore_, int deltaTime_, int playerHP_, int liveCount_, int weaponCount_, EnumID weaponID_, int enemyHP_, int _x, int _y, int viewPortX, int viewPortY, int collideId, bool abc, int rang, bool onstair,float checkCameraHaft)
{
	//(int gameStage_, int playerScore_, int deltaTime_, int playerHP_, int liveCount_, EnumID weaponID_, int weaponCount_, int enemyHP_)
	_gameStage = gameStage_;
	_playerScore = playerScore_;
	if (_gameTimer <= 0)
	{
	}
	else
		_gameTimer = _gameTimer - deltaTime_;
	_weaponCount = weaponCount_;
	_playerHP = playerHP_;
	_enemyHP = enemyHP_;
	_liveCount = liveCount_;
	_playerX = _x;
	_playerY = _y;
	_viewPortY = viewPortY;
	_viewPortX = viewPortX;
	_collideID = collideId;
	_rang = rang;
	//if (checkCameraHaft == true)
	//	_checkCameraHaft = 1;
	//else _checkCameraHaft = 0;
	_checkCameraHaft = checkCameraHaft;
	if (abc == true)
		_colabc = 1;
	else _colabc = 0;
	if (onstair == true)
		_onstair = 1;
	else _onstair = 0;
	switch (weaponID_)
	{

	case Dagger_ID:
		_currentWeapon = 0;
		break;
	case Boomerang_ID:
		_currentWeapon = 1;
		break;
	case Throw_Axe_ID:
		_currentWeapon = 2;
		break;
	case StopWatch_ID:
		_currentWeapon = 3;
		break;

	case HolyWater_ID:
		_currentWeapon = 4;
		break;
	default:
		_currentWeapon = -1;
		break;
	}

}

GameUI::~GameUI(void)
{
}
