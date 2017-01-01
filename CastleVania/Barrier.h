#ifndef _BARRIER_H_
#define _BARRIER_H_

#include "GameObject.h"
#include "EnumManager.h"

class Barrier : public GameObject
{
public:
	Barrier(void);
	Barrier(float _posX, float _posY, int _width, int _height);
	~Barrier(void);
};

#endif