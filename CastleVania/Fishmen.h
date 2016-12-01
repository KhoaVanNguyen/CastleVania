#ifndef _Fishmen_H_
#define _Fishmen_H_

#include "DynamicObject.h"
#include "CEnum.h"
#include "Water.h"
#include "FireBall.h"

class Fishmen : public DynamicObject
{
private:
	void Jump();
public:
	bool _hasJump;
	float _heightJump;
	list<Water*> *w;
	list<FireBall*> *fireBall;

	Fishmen(void);
	Fishmen(float x, float y);
	void Update(int dt);
	void Draw(GCamera* camera);
	void Collision(list<GameObject*> obj, int dt);
	void SetActive(float x, float y);
	~Fishmen(void);
};
#endif
