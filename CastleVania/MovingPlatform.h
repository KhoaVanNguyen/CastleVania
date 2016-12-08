#ifndef _MOVINGPLATFORM_H_
#define _MOVINGPLATFORM_H_

#include "DynamicObject.h"

class MovingPlatform : public DynamicObject
{
public:
	MovingPlatform(void);
	MovingPlatform(float x, float y);
	void Draw(GCamera* camera);
	~MovingPlatform(void);
};

#endif