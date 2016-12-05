#include "Stair.h"


Stair::Stair(void) : GameObject()
{
}

Stair::Stair(float _posX, float _posY, int _width, int _height, EnumID _id) :
GameObject(_posX, _posY, _id)
{
	width = _width;
	height = _height;
}

Stair::~Stair(void)
{
}
