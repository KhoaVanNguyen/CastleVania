#include "Candle.h"
#include "CEnum.h"

Candle::Candle(void) : GameObject()
{
	
}

Candle::Candle(float _x, float _y) : GameObject(_x, _y, EnumID::Candle_ID)
{
	canBeKilled = true;
	point = 5;
	hp = 10;
}

Candle::~Candle(void)
{
}
