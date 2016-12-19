
#include "MagicalBall.h"


MagicalBall::MagicalBall(void) : DynamicObject()
{
}

MagicalBall::MagicalBall(float x, float y) : DynamicObject(x, y, 0, -0.3f, EnumID::MagicalBall_ID)
{
	active = true;
	type = ObjectType::Item;
}

void MagicalBall::Collision(list<GameObject*> obj, int dt)
{
	list<GameObject*>::iterator _itBegin;
	for (_itBegin = obj.begin(); _itBegin != obj.end(); _itBegin++)
	{
		GameObject* other = (*_itBegin);

		if (other->id == EnumID::Brick_ID)
		{
			float moveX;
			float moveY;
			float normalx;
			float normaly;
			Box box = this->GetBox();
			Box boxOther = other->GetBox();

			if (AABB(box, boxOther, moveX, moveY) == true)
			{
				posY += moveY;
				vY = 0;
				return;
			}
		}
	}
}

MagicalBall::~MagicalBall(void)
{
}
