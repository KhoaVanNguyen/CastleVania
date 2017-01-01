#ifndef _FireBossDie_H_
#define _FireBossDie_H_

#include "DynamicObject.h"
#include "EnumManager.h"
#include <time.h>
#include <random>


class FireBossDie :public GameObject
{
public:
	int deltatime;
	FireBossDie(void);
	FireBossDie(float _posX, float _posY, int _width, int _height);
	//void Update(int dt);
	//void Collision(list<GameObject*> obj, int dt);
	~FireBossDie(void);
};

#endif