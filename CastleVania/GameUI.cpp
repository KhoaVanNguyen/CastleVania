#include "GameUI.h"


void GameUI::_initialize()
{
	// init weaponSprite
	weapons = vector<GSprite*>();
	weapons.push_back(new GSprite(Singleton::getInstance()->getTexture(EnumID::Dagger_ID), 1));
	weapons.push_back(new GSprite(Singleton::getInstance()->getTexture(EnumID::Boomerang_ID), 1));
	weapons.push_back(new GSprite(Singleton::getInstance()->getTexture(EnumID::Throw_Axe_ID), 1));



	// init hp sprite
	_hpSprite = new GSprite(Singleton::getInstance()->getTexture(EnumID::HP_ID), 1);

	_gameTimer = 0;
}
GameUI::GameUI(LPDIRECT3DDEVICE9 d3ddev_, int size_, int screenWidth_, int screenHeight_)
{
	this->_initialize();
	_sprite = new GSprite(Singleton::getInstance()->getTexture(EnumID::GameUI_ID), 1);
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
	_arial->render("PASS GAME :))", 5, 60);
	_arial->render(_liveCount, 420, 30);
	_arial->render(_weaponCount, 430, 50);
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

void GameUI::SetSimonScore(int x)
{
	_playerScore += x;
}

GameUI::GameUI(void)
{

}




void GameUI::updateScore(int gameStage_, int simonScore_, int deltaTime_, int simonHP_, int liveCount_, int weaponCount_, EnumID weaponID_, int enemyHP_)
{
//(int gameStage_, int simonScore_, int deltaTime_, int simonHP_, int liveCount_, EnumID weaponID_, int weaponCount_, int enemyHP_)
	_gameStage = gameStage_;
	_playerScore = simonScore_;
	if (_gameTimer <= 0)
	{
	}
	else
	_gameTimer = _gameTimer - deltaTime_;
	_weaponCount = weaponCount_;
	_playerHP = simonHP_;
	_enemyHP = enemyHP_;
	_liveCount = liveCount_;

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


GameUI::~GameUI(void)
{
}
