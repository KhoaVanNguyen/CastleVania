
#include "MovingPlatform.h"


MovingPlatform::MovingPlatform(void) : DynamicObject()
{
}

MovingPlatform::MovingPlatform(float x, float y) : DynamicObject(x, y, 0.1f, 0, EnumID::MovingPlatform_ID)
{
	active = true;
}

void MovingPlatform::Draw(GCamera* camera)
{
	if (sprite != NULL)
	{
		D3DXVECTOR2 center = camera->Transform(posX, posY);
		sprite->Draw(center.x, center.y);
	}
}

MovingPlatform::~MovingPlatform(void)
{
}
