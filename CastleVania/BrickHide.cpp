#include "BrickHide.h"


BrickHide::BrickHide(void) : GameObject()
{
}

BrickHide::BrickHide(float _x, float _y) : GameObject(_x, _y, EnumID::BrickHide_ID)
{
	canBeKilled = true;
	point = 5;
	hp = 1;
}

BrickHide::~BrickHide(void)
{
}