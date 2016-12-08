#ifndef _BoneTowers_H_
#define _BoneTowers_H_

#include "DynamicObject.h"
#include "FireBall.h"

class BoneTowers : public DynamicObject
{
	list<FireBall*> *fireBall;
public:
	BoneTowers(void);
	BoneTowers(float x, float y);
	void Update(int dt);
	void Draw(GCamera* camera);
	void SetActive(float x, float y);
	~BoneTowers(void);
};

#endif