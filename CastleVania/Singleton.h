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
	GTexture* Ghouls;
	GTexture* Bats;
	GTexture* MedusaHeads;
	GTexture* Panthers;
	GTexture* Fishmen;
	GTexture *AxeKnights;


	
	GTexture* BoneTowers;
	
	//ground
	GTexture* candle;
	GTexture* largeCandle;
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
	GTexture* largeHeart;
	GTexture* smallHeart;
	GTexture* moneyBagItem;
	GTexture* crossItem;
	GTexture* whipUpgrade;
	GTexture* holyWater;
	GTexture* boomerangItem;
	GTexture* throwAxe;
	GTexture* stopWatch;
	GTexture* magicalCrystal;
	GTexture *watchItem;

	//boss
	GTexture* phantombat;
	GTexture* Medusa;
	GTexture* littleSnake;

	//other
	GTexture* rewardItem;
	GTexture* water;
	GTexture* fireBall;

	GTexture* bgMenu;

	GTexture* gameScore;
	GTexture* hp;

	GTexture* fallingCastle;
	GTexture* playerInCastle;

	//weapon
	
	static Singleton *single;



	Singleton();

public:
	static Singleton* getInstance();
	~Singleton();
	GTexture* getTexture(EnumID id);
};

#endif