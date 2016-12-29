#pragma once
#include "dynamicobject.h"
class Bandages :
	public DynamicObject
{
public:
	Bandages(void);
	Bandages(float posX, float posY, float vX, float vY, EnumID id);
	void Draw(GCamera* camera);
	void Collision(list<GameObject*>, int);
	~Bandages(void);
};

