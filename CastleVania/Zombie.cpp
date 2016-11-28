#include "Zombie.h"


Zombie::Zombie(void) : DynamicObject()
{
}

Zombie::Zombie(float _x, float _y) : DynamicObject(_x, _y, 0.3f, 0, EnumID::Zombie_ID)
{
	type = ObjectType::Enemy_Type;
	//point = 100;
}

Zombie::~Zombie(void)
{
}
