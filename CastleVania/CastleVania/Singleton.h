#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include "GTexture.h"

class Singleton
{
private:
	GTexture* player;
	GTexture* playerDeath;

	//ground
	GTexture* candle;
	GTexture* largeCandle;
	static Singleton *single;
	Singleton();

public:
	static Singleton* getInstance();
	~Singleton();
	GTexture* getTexture(EnumID id);
};

#endif