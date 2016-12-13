#include "CastleGate.h"


CastleGate::CastleGate(void) : GameObject()
{
}

CastleGate::CastleGate(float _posX, float _posY, int _width, int _height) :
GameObject(_posX, _posY, EnumID::CastleGate_ID)
{
	width = _width;
	height = _height;
}

CastleGate::~CastleGate(void)
{
}
