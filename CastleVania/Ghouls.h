#ifndef _Ghouls_H_
#define _Ghouls_H_

#include "DynamicObject.h"
#include "CEnum.h"

class Ghouls :public DynamicObject
{
public:
	Ghouls(void);
	Ghouls(float x, float y);
	//void Update(int deltaTime);
	~Ghouls(void);
};

#endif