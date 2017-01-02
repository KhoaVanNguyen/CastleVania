#include "Mummy.h"


Mummy::Mummy(void) : DynamicObject()
{
}



Mummy::~Mummy()
{
}

Mummy::Mummy(float posX_, float posY_) : DynamicObject(posX_, posY_, 1.8f, 0, EnumID::Mummy_ID)
{
	_bandages = new list<DynamicObject*>();
	_localTime = 0;
	active = true;
	type = ObjectType::Enemy_Type;
	hp = 50;
	damage = 5;
	canBeKilled = true;
	neededPlayerPosition = true;
	_state = EMummyState::Mummy_Moving;
	_isSleeping = true;
	deltaX = 0;
	oldX = posX;
	timeDelay = 50;
	_timeSpan = 0;
	
}

void Mummy::Draw(GCamera* camera)
{
	if (sprite == NULL || !active)
		return;
	D3DXVECTOR2 center = camera->Transform(posX, posY);
	if (vX < 0)
		sprite->Draw(center.x, center.y);
	else
		sprite->DrawFlipX(center.x, center.y);
	_drawBandages(camera);
}



void Mummy::Update(int playerX, int playerY, int deltaTime)
{
	int randomDeltaX;
	_timeSpan+= deltaTime;
	if (_timeSpan % 25 == 0){
		_bandages->push_back(new Bandages(posX, posY, vX*0.06f, 0.0f, EnumID::Bandage_ID));
	}
	switch (_state)
	{
	case EMummyState::Mummy_Stoping:
		sprite->Update(deltaTime);
		_localTime += deltaTime;
		if (_localTime >= 400)
		{
			_localTime = 0;
			_state = EMummyState::Mummy_Moving;
			return;
		}
		break;
	case EMummyState::Mummy_Moving:
		if (posX <= 6800 || posX >=7125 )
			vX = -vX;
		deltaX += (abs(oldX - posX));
		oldX = posX;
		if (playerX > posX){
			posX += vX*deltaTime;
		}
		else {
			posX -= vX*deltaTime;
			}
		sprite->Update(deltaTime);

		 randomDeltaX = rand() % 120 + 20;
		if (deltaX >= 20)
		{
			deltaX = 0;
			this->_state = EMummyState::Mummy_Stoping;
			return;
		}


		break;
	default:
		break;

	}
	_updateBandages(deltaTime);

}



void Mummy::_updateBandages(int deltaTime_)
{
	list<DynamicObject*>::iterator it = _bandages->begin();
	while (it != _bandages->end())
	{
		if (!(*it)->active)
			_bandages->erase(it++);
		else
		{
			(*it)->Update(deltaTime_);
			++it;
		}
	}

}

void Mummy::_drawBandages(GCamera* camera_)
{
	for (list<DynamicObject*>::iterator iter = _bandages->begin(); iter != _bandages->end(); iter++)
	{
		DynamicObject* tempSnake = (*iter);
		tempSnake->Draw(camera_);
	}
}

void Mummy::Collision(list<GameObject*> obj, int dt) {
	list<GameObject*>::iterator _itBegin;
	for (_itBegin = obj.begin(); _itBegin != obj.end(); _itBegin++)
	{
		float moveX = 0;
		float moveY = 0;
		float normalx;
		float normaly;
		GameObject* other = (*_itBegin);
		if (other->id == EnumID::Brick_ID)
		{
			Box box = this->GetBox();
			Box boxOther = other->GetBox();

			if (AABB(box, boxOther, moveX, moveY) == true)
			{
				/*if (vY < 0)
				{
					posY += moveY + 20;
					vY = 0;
					return;
				}
				if ((posX - width / 2 + 10) - (other->posX - other->width / 2) <= 0
					|| (posX + width / 2 - 10) - (other->posX + other->width / 2) >= 0)
					vX = -vX;*/
			}
			
		}
	}
}