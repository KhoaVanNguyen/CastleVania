#ifndef _LARGECANDLE_H_
#define _LARGECANDLE_H_

#include "GameObject.h"

class LargeCandle : public GameObject
{
public:
	LargeCandle(void);
	LargeCandle(float _x, float _y);
	~LargeCandle(void);
};

#endif