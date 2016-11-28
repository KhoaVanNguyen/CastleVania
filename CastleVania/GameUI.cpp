#include "GameUI.h"


void GameUI::_initialize()
{
	// init weaponSprite

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
	for (int i = 0; i<_simonHP; i++)
	{
		_hpSprite->DrawIndex(0, 100 + 10 * i, 30);
	}
	for (int i = _simonHP; i<MAX_HP; i++)
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
	/*if (_currentWeapon != -1)
	{
		_vWeaponSprite.at(_currentWeapon)->Draw(345, 48);
	}*/
}

void GameUI::drawScore()
{
	_arial->onLost();
	_arial->render("Score", 5, 0);
	_arial->render(_simonScore, 100, 0);
	_arial->render("TIME", 230, 0);
	_arial->render(_gameTimer / 1000, 310, 0);
	_arial->render("STAGE", 400, 0);
	_arial->render(_gameStage, 490, 0);
	_arial->render("PLAYER", 5, 20);
	_arial->render("ENEMY", 5, 40);
	_arial->render("PASS GAME :))", 5, 60);
	_arial->render(_weaponCount, 420, 30);
	_arial->render(_liveCount, 430, 50);
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
	_simonScore += x;
}

GameUI::GameUI(void)
{

}




void GameUI::updateScore(int gameStage_, int simonScore_, int deltaTime_, int simonHP_, int liveCount_, EnumID weaponID_, int weaponCount_, int enemyHP_)
{
	_gameStage = gameStage_;
	_simonScore = simonScore_;
	if (_gameTimer <= 0)
	{
	}
	else
		_gameTimer = _gameTimer - deltaTime_;
	_weaponCount = weaponCount_;
	_simonHP = simonHP_;
	_enemyHP = enemyHP_;
	_liveCount = liveCount_;

	

}


GameUI::~GameUI(void)
{
}
