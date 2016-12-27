#include "Barrier.h"
Barrier::Barrier(void) : GameObject()
{
}
Barrier::Barrier(float _posX, float _posY, int _width, int _height) :
	GameObject(_posX, _posY, EnumID::Barrier_ID)
{
	width = _width;
	height = _height;
}
Barrier::~Barrier(void)
{
}
