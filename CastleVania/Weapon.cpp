#include "Weapon.h"

#define SPEED_X 0.5f

Weapon::Weapon(void)
{

}

Weapon::Weapon(float x, float y, float _huong, EnumID id) : DynamicObject(x, y, 0, 0, id)
{
	if (_huong > 0)
		vX = SPEED_X;
	else
	{
		vX = -SPEED_X;
	}
	active = true;
}

void Weapon::Draw(GCamera* camera)
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
		sprite->Draw(center.x, center.y);
	else
		sprite->DrawFlipX(center.x, center.y);
}

void Weapon::Update(int dt)
{
	if (sprite == NULL || !active)
		return;
	posX += vX*dt;
	posY += vY*dt;
	sprite->Update(dt);
}
void Weapon::Collision(list<GameObject*> &obj, int dt)
{
	list<GameObject*>::reverse_iterator _itBegin;
	for (_itBegin = obj.rbegin(); _itBegin != obj.rend(); _itBegin++)
	{
		GameObject* other = (*_itBegin);
	
			float moveX;
			float moveY;

			Box box = this->GetBox();
			Box boxOther = other->GetBox();

			if (AABB(box, boxOther, moveX, moveY) == true)
			{

				if (other->canBeKilled)
				{
					if (other->id == EnumID::Medusa_ID)
					{
						Medusa* qm = (Medusa*)other;
						if (qm->HasGetUp)
						{
							other->ReceiveDamage(damage);
							if (other->hp <= 0)
							{
								point += other->point;
							}
						}
						else
							qm->getUp();
					}
					else
					{
						other->ReceiveDamage(damage);
						if (other->hp <= 0)
						{
							point += other->point;
							(*_itBegin) = new RewardItem(other->posX, other->posY);
						}

					}

				}
				return;
			}
		
	}
}

Weapon::~Weapon(void)
{

}
