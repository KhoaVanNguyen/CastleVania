#ifndef _FIREBALL_H_
#define _FIREBALL_H_

#include "DynamicObject.h"

class FireBall : public DynamicObject
{
	int _timeSpawn;
public:
	FireBall(void);
	FireBall(float x, float y, float _huong, EnumID id);
	void Update(int dt);
	~FireBall(void);
};

#endif