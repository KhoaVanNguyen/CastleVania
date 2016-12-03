#include "Water.h"

#define SPEED_X 0.25f
#define SPEED_Y 0.2f
#define MAX_HEIGHT 30.0f

Water::Water(void) : DynamicObject()
{
}

Water::Water(float x, float y, float vx) : DynamicObject(x, y, vx, 0, EnumID::Water_ID)
{
	active = true;
	_hasJump = false;
	_heightJump = 0;
	deltatime = 0;
	Jump();
}

void Water::Update(int dt)
{
	deltatime += dt;
	if (deltatime >= 1000)
	{
		sprite = NULL;
	}
	posX += vX*dt;
	posY += vY*dt;
	if (_hasJump)
	{
		_heightJump += vY * dt;
		if (_heightJump >= MAX_HEIGHT)
		{
			_hasJump = false;
			vY = -(SPEED_Y + 0.3f);
		}
	}
}

void Water::Jump()
{
	vY = SPEED_Y;
	_hasJump = true;
	_heightJump = 0.0f;
}

Water::~Water(void)
{
}
