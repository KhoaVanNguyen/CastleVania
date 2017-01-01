#ifndef _MagicalBall_H_
#define _MagicalBall_H_

#include "DynamicObject.h"
#include "EnumManager.h"

class MagicalBall : public DynamicObject
{
public:
	MagicalBall(void);
	MagicalBall(float x, float y);
	void Collision(list<GameObject*> obj, int dt);
	~MagicalBall(void);
};

#endif