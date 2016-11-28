#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include "GTexture.h"
#include "CEnum.h"

class Singleton
{
private:
	GTexture* player;
	GTexture* playerDeath;

	//enemy
	GTexture* zombie;
	GTexture* blackKnight;
	GTexture* blackLeopard;
	GTexture* fishMan;
	GTexture* dragonSkullCannon;
	GTexture* vampireBat;
	GTexture* medusa;
	//ground
	GTexture* candle;
	GTexture* largeCandle;
<<<<<<< HEAD
	GTexture* movingPlatform;
	GTexture* openDoor;
	GTexture* stupidDoor;
	//weapon
	GTexture* morningStar;
	GTexture* fireBomb;
	GTexture* dagger;
	GTexture* boomerang;
	GTexture* axe;
	//item
	GTexture* largeHeartItem;
	GTexture* smallHeartItem;
	GTexture* moneyBagItem;
	GTexture* crossItem;
	GTexture* morningStarItem;
	GTexture* fireBombItem;
	GTexture* daggerItem;
	GTexture* boomerangItem;
	GTexture* axeItem;
	GTexture* watchItem;

	GTexture* magicalCrystal;
	//boss
	GTexture* phantombat;
	GTexture* queenMedusa;
	GTexture* littleSnake;
	//other
	GTexture* fireDie;
	GTexture* water;
	GTexture* fireBall;

	GTexture* bgMenu;
	//IntroScene
	GTexture* helicopter;
	GTexture* bat;
	GTexture* introBackground;

	GTexture* gameScore;
	GTexture* hp;

	GTexture* fallingCastle;
	GTexture* playerInCastle;

=======


	//weapon
	GTexture* morningStar;
>>>>>>> origin/AddFight
	static Singleton *single;



	Singleton();

public:
	static Singleton* getInstance();
	~Singleton();
	GTexture* getTexture(EnumID id);
};

#endif