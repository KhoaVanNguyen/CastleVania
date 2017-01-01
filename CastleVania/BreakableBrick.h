#ifndef _BRICK_HIDE_H_
#define _BRICK_HIDE_H_

#include "DynamicObject.h"
#include "EnumManager.h"

class BreakableBrick :public DynamicObject
{
public:
	BreakableBrick(void);
	BreakableBrick(float _x, float _y);
	~BreakableBrick(void);
};

#endif

