#ifndef _DOOR_H_
#define _DOOR_H_

#include "GameObject.h"
#include "CEnum.h"

class Door : public GameObject
{
public:
	Door(void);
	Door(float _posX, float _posY, int _width, int _height, EnumID _id);
	~Door(void);
};

#endif