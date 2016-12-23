#ifndef _CenterOfCircle_H_
#define _CenterOfCircle_H_

#include "GameObject.h"
#include "CEnum.h"

class CenterOfCircle : public GameObject
{
public:
	CenterOfCircle(void);
	CenterOfCircle(float _posX, float _posY, int _width, int _height);
	~CenterOfCircle(void);
};

#endif