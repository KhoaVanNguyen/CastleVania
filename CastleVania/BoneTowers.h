#ifndef _BoneTowers_H_
#define _BoneTowers_H_

#include "DynamicObject.h"
#include "Fire.h"

class BoneTowers : public DynamicObject
{
	list<DynamicObject*>*_listFire;
	void _upDateFire(float t);
	void _drawFire(GCamera* camera);
	int _timeSpan;
public:
	BoneTowers(void);
	BoneTowers(float x, float y);
	void Update(int dt);
	void Draw(GCamera* camera);
//	void SetActive(float x, float y);
	~BoneTowers(void);
	void Collision(list<GameObject*> obj, int dt);
	
};

#endif