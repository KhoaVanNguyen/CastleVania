#include "Door.h"


Door::Door(void) : GameObject()
{
}

Door::Door(float _posX, float _posY, int _width, int _height, EnumID _id) :
GameObject(_posX, _posY, _id)
{
	width = _width;
	height = _height;
	sprite = NULL;
}

Door::~Door(void)
{
}
