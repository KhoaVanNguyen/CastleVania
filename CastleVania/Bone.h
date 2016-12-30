#pragma once
#include "DynamicObject.h"
class Bone :
	public DynamicObject
{
public:
	Bone(void);
	Bone(float posX, float posY, float vX, float vY, EnumID id);
	void Draw(GCamera* camera);
	void Collision(list<GameObject*>, int);
	~Bone(void);
};

