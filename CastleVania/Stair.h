#ifndef _STAIR_H_
#define _STAIR_H_

#include "GameObject.h"
#include "EnumManager.h"

class Stair : public GameObject
{
public:
	Stair(void);
	Stair(float _posX, float _posY, int _width, int _height, EnumID _id);
	~Stair(void);
};

#endif