#include "LittleSnake.h"


LittleSnake::LittleSnake(void)
{
}

LittleSnake::LittleSnake(float _posX, float _posY, float _vX, float _vY, EnumID _id)
	: DynamicObject(_posX, _posY, _vX, _vY, _id)
{
	active = true;
	canBeKilled = true;
}

void LittleSnake::Draw(GCamera* camera)
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

void LittleSnake::Collision(list<GameObject*> obj, int dt)
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

LittleSnake::~LittleSnake(void)
{
}
