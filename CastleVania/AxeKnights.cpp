
#include "AxeKnights.h"


AxeKnights::AxeKnights(void) : DynamicObject()
{
}

AxeKnights::AxeKnights(float x, float y) : DynamicObject(x, y, 0.08f, 0, EnumID::AxeKnights_ID)
{
	type = ObjectType::Enemy_Type;
	point = 400;
	hp = 2;
	damage = 2;
	canBeKilled = true;
}

AxeKnights::~AxeKnights(void)
{
}


