#ifndef _Fire_H_
#define _Fire_H_

#include "DynamicObject.h"

class Fire : public DynamicObject
{
	int _timeSpawn;
public:
	Fire(void);
	Fire(float x, float y,  EnumID id);
	void Update(int dt);
	~Fire(void);
	void Draw(GCamera *camera);
	void Collision(list<GameObject*> obj, int dt);
};

#endif