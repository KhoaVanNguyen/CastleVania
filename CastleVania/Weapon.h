#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "DynamicObject.h"
#include "RewardItem.h"
#include "Medusa.h"
class Weapon : public DynamicObject
{
public:
	Weapon(void);
	Weapon(float x, float y, float _huong, EnumID id);
	virtual void Draw(GCamera*);
	virtual void Collision(list<GameObject*> &obj, int dt);
	//virtual void Collision(Box playerBox);
	void Update(int dt);
	~Weapon(void);
};

#endif