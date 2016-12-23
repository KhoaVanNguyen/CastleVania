#ifndef _BRICKCOLLISION_H_
#define _BRICKCOLLISION_H_

#include "GameObject.h"
#include "CEnum.h"

class BrickCollision : public GameObject
{
public:
	BrickCollision(void);
	BrickCollision(float _posX, float _posY, int _width, int _height);
	~BrickCollision(void);
};

#endif