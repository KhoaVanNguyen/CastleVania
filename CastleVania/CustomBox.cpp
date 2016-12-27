#include "CustomBox.h"


CustomBox::CustomBox()
{
}
CustomBox::CustomBox(float _x, float _y, float _w, float _h, float _vx, float _vy)
{
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	vx = _vx;
	vy = _vy;
}

CustomBox::CustomBox(float _x, float _y, float _w, float _h)
{
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	vx = 0.0f;
	vy = 0.0f;
}

CustomBox::~CustomBox()
{
}
