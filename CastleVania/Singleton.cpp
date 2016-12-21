#include "Singleton.h"
#include <string>
#include <sstream>
#include <windows.h>
#include <iostream>
#include <malloc.h>

using namespace std;

Singleton* Singleton::single = NULL;

Singleton* Singleton::getInstance()
{
	if (single == NULL)
		single = new Singleton();
	return single;
}

Singleton::Singleton()
{
	player = new GTexture("Resources/player.png", 8, 3, 24);

	morningStar = new GTexture("Resources/morningstar.png", 3, 3, 9);
	//playerDeath = new GTexture("Resources/playerdeath.png", 1, 1, 1);

	//Enemy
	Ghouls = new GTexture("Resources/enemy/1.png", 2, 1, 2);
	MedusaHeads = new GTexture("Resources/enemy/6.png", 2, 1, 2);
	Bats = new GTexture("Resources/enemy/0.png", 4, 1, 4);
	Panthers = new  GTexture("Resources/enemy/2.png", 4, 1, 4);
	Fishmen = new GTexture("Resources/enemy/3.png", 3, 1, 3);
	AxeKnights = new GTexture("Resources/enemy/5.png", 4, 1, 4);
	BoneTowers = new GTexture("Resources/enemy/8.png", 1, 1, 1);

	//ground
	candle = new GTexture("Resources/ground/1.png", 4, 1, 4);
	largeCandle = new GTexture("Resources/ground/0.png", 2, 1, 2);
	movingPlatform = new GTexture("Resources/ground/9.png", 1, 1, 1);
	TrapDoor = new GTexture("Resources/ground/7_3.png", 2, 1, 2);
	//bosses
	Medusa = new GTexture("Resources/boss/1.png", 5, 1, 5);
	phantombat = new GTexture("Resources/boss/0.png", 3, 1, 3);
	littleSnake = new GTexture("Resources/boss/2.png", 2, 1, 2);

	largeHeart = new GTexture("Resources/item/1.png", 1, 1, 1);
	smallHeart = new GTexture("Resources/item/0.png", 1, 1, 1);
	moneyBagItem = new GTexture("Resources/item/2.png", 3, 1, 3);
	crossItem = new GTexture("Resources/item/6.png", 1, 1, 1);
	fireBomb = new GTexture("Resources/item/9.png", 1, 1, 1);
	dagger = new GTexture("Resources/item/4.png", 1, 1, 1);
	boomerangItem = new GTexture("Resources/item/8.png", 1, 1, 1);
	axe = new GTexture("Resources/item/7.png", 1, 1, 1);

	// remove later 
	whipUpgrade = new GTexture("Resources/item/3.png", 1, 1, 1);
	

	holyWater = new GTexture("Resources/item/9.png", 1, 1, 1);
	dagger = new GTexture("Resources/item/4.png", 1, 1, 1);
	boomerangItem = new GTexture("Resources/item/8.png", 1, 1, 1);
	throwAxe = new GTexture("Resources/item/7.png", 1, 1, 1);
	stopWatch = new GTexture("Resources/item/5.png", 1, 1, 1);

	MagicalBall = new GTexture("Resources/item/13.png", 2, 1, 2);

	
	//MedusaHeads = new GTexture("Resources/boss/1.png", 5, 1, 5);
	littleSnake = new GTexture("Resources/boss/2.png", 2, 1, 2);

	fireBossDie = new GTexture("Resources/other/1.png", 3, 1, 3);
	water = new GTexture("Resources/other/2.png", 1, 1, 1);
	fireBall = new GTexture("Resources/fireball.png", 1, 1, 1);

	bgMenu = new GTexture("Resources/mainmenu.png", 1, 1, 1);

	gameScore = new GTexture("Resources/blackboard.png", 1, 1, 1);
	hp = new GTexture("Resources/heal.png", 3, 1, 3);

	fallingCastle = new GTexture("Resources/FallingCastle.png", 3, 1, 3);
	
	//door
	openDoor = new GTexture("Resources/ground/Gate1.png", 4, 1, 4);

	// Item
	rewardedItem = new GTexture("Resources/other/1.png", 3, 1, 3);
	crossItem = new GTexture("Resources/item/6.png", 1, 1, 1);
	porkChop = new GTexture("Resources/item/10.png", 1, 1, 1);
	
	
	
	watchItem = new GTexture("Resources/item/5.png", 1, 1, 1);

}

GTexture* Singleton::getTexture(EnumID id)
{
	switch (id)
	{
	case EnumID::Player_ID:
		return player;
	case EnumID::PlayerDeath_ID:
		return playerDeath;

		//Enemy
	case EnumID::Ghouls_ID:
		return Ghouls;
	case EnumID::MedusaHeads_ID:
		return MedusaHeads;
	case EnumID::Bats_ID:
		return Bats;
	case EnumID::Panthers_ID:
		return Panthers;
	case EnumID::Fishmen_ID:
		return Fishmen;
	case EnumID::AxeKnights_ID:
			return AxeKnights;
	case EnumID ::BoneTowers_ID:
		return BoneTowers;
		
	case EnumID::FireBall_ID:
		return fireBall;
		//ground
	case EnumID::Candle_ID:
		return candle;
	case EnumID::LargeCandle_ID:
		return largeCandle;
	case EnumID ::MovingPlatform_ID:
		return movingPlatform;
	case EnumID::MorningStar_ID:
		return morningStar;
	case EnumID::Water_ID:
		return water;
		//Boss
	case EnumID::PhantomBat_ID:
		return phantombat;
	case EnumID::Medusa_ID:
		return Medusa;
	case EnumID::LittleSnake_ID:
		return littleSnake;
		// Other
		
	case EnumID::FireBossDie_ID:
		return fireBossDie;
			
		// Door

	case EnumID::OpenDoor_ID:
		return openDoor;
	case EnumID::TrapDoor_ID:
		return TrapDoor;

	// GameUI
	case EnumID::HP_ID:
		return hp;

	case EnumID::GameUI_ID:
		return gameScore;

		// Items:

	
	case EnumID::Large_Heart:
		return largeHeart;
	case EnumID::Small_Heart:
		return smallHeart;

	case EnumID::Red_Money_Bag:
		return moneyBagItem;
	case EnumID::MoneyBagItem_ID:
		return moneyBagItem;
	case EnumID::Purple_Money_Bag:
		return moneyBagItem;
	case EnumID::White_Money_Bag:
		return  moneyBagItem;
	
	case EnumID::Whip_Upgrade:
		return whipUpgrade;
	case EnumID::Dagger_ID:
		return  dagger;
	case EnumID::Throw_Axe_ID:
		return throwAxe;
	case EnumID::Holy_Watter_ID:
		return holyWater;
	case EnumID::Boomerang_ID:
		return boomerangItem;
	case EnumID::StopWatch_ID:
		return stopWatch;
		
	case EnumID::MagicalBall_ID:
		return MagicalBall;

	case EnumID::PorkChop_ID:
		return porkChop;
	case EnumID::RewardedItem_ID:
		return rewardedItem;
	case EnumID::CrossItem_ID:
		return crossItem;

	
		/*moneyBagItem = new GTexture("Resources/item/2.png", 3, 1, 3);
		crossItem = new GTexture("Resources/item/6.png", 1, 1, 1);
		morningStarItem = new GTexture("Resources/item/3.png", 1, 1, 1);*/
		
		/*fireBombItem = new GTexture("Resources/item/9.png", 1, 1, 1);
		daggerItem = new GTexture("Resources/item/4.png", 1, 1, 1);
		boomerangItem = new GTexture("Resources/item/8.png", 1, 1, 1);
		axeItem = new GTexture("Resources/item/7.png", 1, 1, 1);*/
		
		
	/*	watchItem = new GTexture("Resources/item/5.png", 1, 1, 1);

		MagicalBall = new GTexture("Resources/item/13.png", 2, 1, 2);*/
	}
}