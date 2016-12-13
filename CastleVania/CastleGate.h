#ifndef _CASTLEGATE_H_
#define _CASTLEGATE_H_

#include "GameObject.h"
#include "CEnum.h"

class CastleGate : public GameObject
{
public:
	CastleGate(void);
	CastleGate(float _posX, float _posY, int _width, int _height);
	~CastleGate(void);
};

#endif