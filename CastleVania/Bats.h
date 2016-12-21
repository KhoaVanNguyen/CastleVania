#ifndef _BAT_H_
#define _BAT_H_

#include "DynamicObject.h"
#include "CEnum.h"

class Bats :public DynamicObject
{
public:
	bool getUp;

	float limit;
	Bats(void);
	Bats(float x, float y);
	void MoveSinPath(int deltaTime);
	void Update(int deltaTime);
	void Draw(GCamera* camera);
	void SetActive(float x, float y);
	void Collision(list<GameObject*> obj, int dt);
	~Bats(void);
};

#endif