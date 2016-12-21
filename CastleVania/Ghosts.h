#pragma once
#include "DynamicObject.h"
#include "CEnum.h"
#define PI 3.14f
#define T 1000
#define A 10
class Ghosts : public DynamicObject
{
	float _posY0;
	float _deltaPhi;
public:
	
	~Ghosts();
	Ghosts(void);
	Ghosts(float x, float y);
	void Update(int dt);
};



 