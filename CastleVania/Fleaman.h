#ifndef _FLEAMAN_H_
#define _FLEAMAN_H_

#include "DynamicObject.h"
#include "CEnum.h"

class Fleaman :public DynamicObject
{
private:
	void Jump();
public:
	bool _hasJump;
	float _heightJump;

	Fleaman(void);
	Fleaman(float _x, float _y);
	void Update(int dt);
	void Collision(list<GameObject*> obj, int dt);
	void SetActive(float x, float y);
	void Draw(GCamera* camera);
	~Fleaman(void);
};

#endif