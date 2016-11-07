#ifndef _CANDLE_H_
#define _CANDLE_H_

#include "GameObject.h"

class Candle : public GameObject
{
public:
	Candle(void);
	Candle(float _x, float _y);
	~Candle(void);
};

#endif