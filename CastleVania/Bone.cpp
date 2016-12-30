#include "Bone.h"

#define SPEED_X 0.2f

Bone::Bone(void) : DynamicObject()
{
}

Bone::Bone(float x, float y, EnumID id) : DynamicObject(x, y, 0.5, 0, id)
{

	_nextStopPos = new D3DXVECTOR2(0, 0);
	_anpha = 0;
	_posX0 = posX;
	_posY0 = posY;


	_anpha = THROW_AXE_ANPHA;
	_posX0 = posX = x + 20;
	_nextStopPos->x = posX + 100;


	_anpha = _anpha*(3.14 / 180);
	_posY0 = posY = y + 20;



	_timeSpawn = 0;
	active = true;
	type = ObjectType::Enemy_Type;
}

void Bone::Update(int dt)
{
	_timeSpawn += dt;
	posX += vX * dt;
	if (_timeSpawn >= 500)
		active = false;



	this->sprite->Update(dt);
	vX = THROW_AXE_SPEED_X*cos(_anpha);
	vY = THROW_AXE_SPEED_X*sin(_anpha) - G*dt;
	posX += vX*dt;
	float deltaPosX = posX - _posX0;
	posY = _posY0 + vY*deltaPosX / vX - 0.5*G*pow((deltaPosX / vX), 2);


}

Bone::~Bone(void)
{
}

void Bone::Draw(GCamera *camera)
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

void Bone::Collision(list<GameObject*> obj, int dt)
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
