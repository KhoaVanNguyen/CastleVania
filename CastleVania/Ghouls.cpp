#include "Ghouls.h"


Ghouls::Ghouls(void) : DynamicObject()
{
}

Ghouls::Ghouls(float _x, float _y) : DynamicObject(_x, _y, 0.3f, 0, EnumID::Ghouls_ID)
{
	type = ObjectType::Enemy_Type;
	//point = 100;
}

Ghouls::~Ghouls(void)
{
}
