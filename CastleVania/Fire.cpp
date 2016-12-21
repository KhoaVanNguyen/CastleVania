#include "Fire.h"

#define SPEED_X 0.2f

Fire::Fire(void) : DynamicObject()
{
}

Fire::Fire(float x, float y, EnumID id) : DynamicObject(x, y, 0.5, 0, id)
{
	_timeSpawn = 0;
	active = true;
	_timeSpawn = 0;
	type = ObjectType::Enemy_Type;
}

void Fire::Update(int dt)
{
	_timeSpawn += dt;
	posX -= vX * dt;
	if (_timeSpawn >= 3000)
	active = false;
}

Fire::~Fire(void)
{
}

void Fire::Draw(GCamera *camera)
{
	if (sprite == NULL || !active)
		return;
	if (posX + width / 2 <= camera->viewport.x || posX - width / 2 >= camera->viewport.x + G_ScreenWidth)
	{
		active = false;
		return;
	}
	D3DXVECTOR2 center = camera->Transform(posX, posY);
	if (vX > 0)
		sprite->DrawFlipX(center.x, center.y);
	else
		sprite->Draw(center.x, center.y);
}

void Fire::Collision(list<GameObject*> obj, int dt)
{
	list<GameObject*>::iterator _itBegin;
	for (_itBegin = obj.begin(); _itBegin != obj.end(); _itBegin++)
	{
		float moveX;
		float moveY;
		GameObject* other = (*_itBegin);
		if (other->id == EnumID::Brick_ID)
		{
			Box box = this->GetBox();
			Box boxOther = other->GetBox();

			if (AABB(box, boxOther, moveX, moveY) == true)
			{
				if (vY < 0)
				{
					posY += moveY;
					vY = 0;
					return;
				}
				if (moveX != 0)
					this->active = false;
			}
		}
	}
}
