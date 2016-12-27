#pragma once
class CustomBox
{
public:
	CustomBox();
	CustomBox(float _x, float _y, float _w, float _h, float _vx, float _vy);
	CustomBox(float _x, float _y, float _w, float _h);
	// position of top-left corner
	float x, y;

	// dimensions
	float w, h;

	// velocity
	float vx, vy;
	~CustomBox();
};

