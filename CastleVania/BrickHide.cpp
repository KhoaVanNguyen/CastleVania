#include "BrickHide.h"


BrickHide::BrickHide(void) : DynamicObject()
{

}

BrickHide::BrickHide(float _x, float _y) : DynamicObject(_x, _y, 0, 0, EnumID::BrickHide_ID)
{
	canBeKilled = true;
	active = true;
	point = 5;
	hp = 1;
}

BrickHide::~BrickHide(void)
{
}