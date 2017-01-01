#ifndef _TextureManager_H_
#define _TextureManager_H_

#include "GTexture.h"
#include "EnumManager.h"

class TextureManager
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
	GTexture *Ghosts;
	GTexture *Ravens;
	GTexture *Fleaman;
	GTexture *Skeletons;
	GTexture *bones;
	GTexture* BoneTowers;

	GTexture* boomerage;

	//ground
	GTexture* candle;
	GTexture* largeCandle;
	GTexture* movingPlatform;
	GTexture* openDoor;
	GTexture* TrapDoor;
	GTexture* BreakableBrick;
	
	//weapon
	GTexture* morningStar;
	GTexture* holyWater;
	GTexture* dagger;
	GTexture* boomerang;
	GTexture* axe;
	//item
	GTexture* largeHeart;
	GTexture* smallHeart;
	GTexture* moneyBagItem;
	GTexture* crossItem;
	GTexture* whipUpgrade;
	GTexture* boomerangItem;
	GTexture* throwAxe;
	GTexture* stopWatch;
	GTexture* MagicalBall;
	GTexture *watchItem;

	//boss
	GTexture* phantombat;
	GTexture* Medusa;
	GTexture* littleSnake;

	GTexture* mummy;
	GTexture* bandages;
	//other
	GTexture* fireBossDie;
	GTexture* water;
	GTexture* Fire;

	GTexture* bgMenu;

	GTexture* gameScore;
	GTexture* hp;

	GTexture* fallingCastle;
	GTexture* playerInCastle;

	// Items
	GTexture* crown;
	GTexture* rewardedItem;
	GTexture* porkChop;
	
	GTexture* holyWaterItem;
	//weapon
	
	static TextureManager *single;

	


	TextureManager();

public:
	static TextureManager* getInstance();
	~TextureManager();
	GTexture* getTexture(EnumID id);
};

#endif