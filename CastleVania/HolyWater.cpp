#include "HolyWater.h"


void HolyWater::_initialize()
{
	_localTime = 0;
	_gold = new D3DXVECTOR2(0, 0);
	_eThrowStatus = EThrowState::Primary;
	_anpha = 0;
	_posX0 = posX;
	_posY0 = posY;
}

HolyWater::HolyWater(void)
{
}

HolyWater::HolyWater(float x_, float y_, float huong_) : Weapon(x_, y_, huong_, EnumID::HolyWater_ID)
{
	_initialize();
	prepareFighting(x_, y_, huong_);
}

void HolyWater::Update(int deltaTime_)
{
	switch (_eThrowStatus)
	{
	case Primary:
		break;
	case Secondary:
		_localTime += deltaTime_;
		this->sprite->Update(deltaTime_);
		if (_localTime >= 500)
			active = false;
		break;
	default:
		break;
	}
	if (_localTime == 0)
	{
		vX = SPEED_X*cos(_anpha);
		vY = SPEED_X*sin(_anpha) - G*deltaTime_;
		posX += vX*deltaTime_;
		float deltaPosX = posX - _posX0;
		posY = _posY0 + vY*deltaPosX / vX - 0.5*G*pow((deltaPosX / vX), 2);
	}
}

void HolyWater::Collision(list<GameObject*> &obj, int dt)
{
	list<GameObject*>::reverse_iterator _itBegin;
	for (_itBegin = obj.rbegin(); _itBegin != obj.rend(); _itBegin++)
	{
		GameObject* other = (*_itBegin);
		if (other->type == ObjectType::Item
			|| other->id == EnumID::MagicalBall_ID || other->id == EnumID::StairDownLeft_ID
			|| other->id == EnumID::StairDownRight_ID || other->id == EnumID::StairUpLeft_ID
			|| other->id == EnumID::StairUpRight_ID || other->id == EnumID::MovingPlatform_ID
			|| other->id == EnumID::TeleDown_ID || other->id == EnumID::TeleUp_ID
			|| other->id == EnumID::DoorLeft_ID || other->id == EnumID::DoorRight_ID
			|| other->id == EnumID::CastleGate_ID || other->id == EnumID::TrapDoor_ID)
		{
		}
		else
		{
			float moveX;
			float moveY;

			Box box = this->GetBox();
			Box boxOther = other->GetBox();

			if (AABB(box, boxOther, moveX, moveY) == true)
			{
				if (other->id != EnumID::Brick_ID)
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
				else
				{
					posY += moveY;
					_localTime += dt;
				}
				sprite->_start = 1;
				_eThrowStatus = EThrowState::Secondary;
				return;
			}
		}
	}
}

void HolyWater::prepareFighting(float simonX_, float simonY_, float direct_)
{
	if (direct_>0)
	{
		_anpha = ANPHA;
		_posX0 = posX = simonX_ + 20;
		_gold->x = posX + 100;
	}
	else
	{
		_anpha = 180 - ANPHA;
		_posX0 = posX = simonX_ - 20;
		_gold->x = posX - 100;
	}
	_anpha = _anpha*(3.14 / 180);
	_posY0 = posY = simonY_ + 20;
}



HolyWater::~HolyWater(void)
{
}
