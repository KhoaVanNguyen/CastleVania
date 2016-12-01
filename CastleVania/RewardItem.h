#ifndef _REWARDITEM_H_
#define _REWARDITEM_H_

#include "DynamicObject.h"
#include "CEnum.h"
#include <time.h>
#include <random>


class RewardItem :public DynamicObject
{
public:
	int deltatime;
	RewardItem(void);
	RewardItem(float x, float y);
	void Update(int dt);
	void Collision(list<GameObject*> obj, int dt);
	~RewardItem(void);
};

#endif