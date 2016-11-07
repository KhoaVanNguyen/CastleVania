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
	simon = new GTexture("Resources/simon.png", 8, 3, 24);
	simonDeath = new GTexture("Resources/simondeath.png", 1, 1, 1);

	candle = new GTexture("Resources/static_object/1.png", 2, 1, 2);
	largeCandle = new GTexture("Resources/static_object/0.png", 2, 1, 2);
}

GTexture* Singleton::getTexture(EnumID id)
{
	switch (id)
	{
	case EnumID::Simon_ID:
		return simon;
	case EnumID::SimonDeath_ID:
		return simonDeath;

	case EnumID::Candle_ID:
		return candle;
	case EnumID::LargeCandle_ID:
		return largeCandle;
	}
}