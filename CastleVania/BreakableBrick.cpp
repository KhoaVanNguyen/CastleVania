#include "BreakableBrick.h"


BreakableBrick::BreakableBrick(void) : DynamicObject()
{

}

BreakableBrick::BreakableBrick(float _x, float _y) : DynamicObject(_x, _y, 0, 0, EnumID::BreakableBrick_ID)
{
	canBeKilled = true;
	active = true;
	point = 5;
	hp = 1;
}

BreakableBrick::~BreakableBrick(void)
{
}