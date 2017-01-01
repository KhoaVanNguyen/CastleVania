#ifndef _BRICK_HIDE_H_
#define _BRICK_HIDE_H_

#include "DynamicObject.h"
#include "EnumManager.h"

class BrickHide :public DynamicObject
{
public:
	BrickHide(void);
	BrickHide(float _x, float _y);
	~BrickHide(void);
};

#endif

