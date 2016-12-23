#include "BrickCollision.h"
BrickCollision::BrickCollision(void) : GameObject()
{
	active = true;
}
BrickCollision::BrickCollision(float _posX, float _posY, int _width, int _height) :
GameObject(_posX, _posY, EnumID::BrickCollision_ID)
{
	width = _width;
	height = _height;
}
BrickCollision::~BrickCollision(void)
{
}
