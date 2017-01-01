#ifndef _WATER_H_
#define _WATER_H_

#include "DynamicObject.h"
#include "EnumManager.h"

class Water : public DynamicObject
{
private:
	void Jump();
public:
	bool _hasJump;
	float _heightJump;
	int deltatime;

	Water(void);
	Water(float x, float y, float vx);
	void Update(int dt);
	~Water(void);
};

#endif