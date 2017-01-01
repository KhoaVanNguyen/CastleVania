#ifndef _REWARDITEM_H_
#define _REWARDITEM_H_

#include "DynamicObject.h"
#include "EnumManager.h"
#include <time.h>
#include <random>


class RewardItem :public DynamicObject
{
public:
	bool _isCrown;
	int deltatime;
	RewardItem(void);
	RewardItem(float x, float y);
	RewardItem(float x, float y, bool isCrown);
	void Update(int dt);
	void Collision(list<GameObject*> obj, int dt);
	~RewardItem(void);
};

#endif