#ifndef _BRICK_H_
#define _BRICK_H_

#include "GameObject.h"
#include "CEnum.h"

class Brick : public GameObject
{
public:
	Brick(void);
	Brick(float _posX, float _posY, int _width, int _height);
	~Brick(void);
};

#endif