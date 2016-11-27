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

	//morningStar = new GTexture("Resources/morningstar.png", 3, 3, 9);
	//playerDeath = new GTexture("Resources/playerdeath.png", 1, 1, 1);
	//candle = new GTexture("Resources/static_object/1.png", 2, 1, 2);
	//largeCandle = new GTexture("Resources/static_object/0.png", 2, 1, 2);
}

GTexture* Singleton::getTexture(EnumID id)
{
	switch (id)
	{
	case EnumID::Player_ID:
		return player;
	case EnumID::PlayerDeath_ID:
		return playerDeath;

	case EnumID::Candle_ID:
		return candle;
	case EnumID::LargeCandle_ID:
		return largeCandle;
	}
}