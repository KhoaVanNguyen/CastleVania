#include "CenterOfCircle.h"
CenterOfCircle::CenterOfCircle(void) : GameObject()
{
}
CenterOfCircle::CenterOfCircle(float _posX, float _posY, int _width, int _height) :
GameObject(_posX, _posY, EnumID::CenterOfCircle_ID)
{
	width = _width;
	height = _height;
}
CenterOfCircle::~CenterOfCircle(void)
{
}
