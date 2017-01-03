#include "Ravens.h"


Ravens::Ravens(void) : DynamicObject()
{
}



Ravens::~Ravens()
{
}

Ravens::Ravens(float posX_, float posY_) :DynamicObject(posX_, posY_, 1.2f, 1.2f, EnumID::Ravens_ID)
{
	neededPlayerPosition = true;
	_localTime = 0;
	active = false;
	type = ObjectType::Enemy_Type;
	hp = 3;
	damage = 4;
	canBeKilled = true;
	_state = ERavenState::moving;
	_isSleeping = true;
	deltaX = 0;
	oldX = posX;
	timeDelay = _timeDelay;
}



void Ravens::Stoping(int deltaTime_)
{
      sprite->Update(deltaTime_);
	_localTime += deltaTime_;
	if (_localTime >= 50)
	{
		_localTime = 0;
		_state = ERavenState::moving;
		return;
	}
}

void Ravens::Moving(int deltaTime_)
{
	deltaX += (abs(oldX - posX));
	oldX = posX;
	posX += vX*deltaTime_;
	posY += vY*deltaTime_;
	sprite->Update(deltaTime_);
	if (deltaX >= 55)
	{
		this->_state = ERavenState::Stoping;
		return;
	}
	
	
}

void Ravens::Draw(GCamera* camera)
{
	if (sprite == NULL || !active)
		return;
	D3DXVECTOR2 center = camera->Transform(posX, posY);
	if (_drawLeft )
		sprite->Draw(center.x, center.y);
	else
		sprite->DrawFlipX(center.x, center.y);
}


void Ravens::Update(int playerX, int playerY, int deltaTime)
{
	if (active)
	{
		switch (_state)
		{
		case ERavenState::Stoping:


			sprite->Update(deltaTime);
			_localTime += deltaTime;
			if (_localTime >= 100)
			{
				_localTime = 0;
				_state = ERavenState::moving;
				return;
			}
			break;
		case ERavenState::moving:
			deltaX += (abs(oldX - posX));
			oldX = posX;

			if (posY <= playerY && posX > playerX) {
				posX += vX*deltaTime;
				posY += vY*deltaTime;
				_drawLeft = true;
			}

			else if (posY <= playerY && posX < playerX){
				posX -= vX*deltaTime;
				posY += vY*deltaTime;
				_drawLeft = false;
			}
			else if (posY >= playerY && posX > playerX){
				posX += vX*deltaTime;
				posY -= vY*deltaTime;
				_drawLeft = true;
			}
			else if (posY >= playerY && posX < playerX) {
				posX -= vX*deltaTime;
				posY -= vY*deltaTime;
				_drawLeft = false;
			}
			sprite->Update(deltaTime);
			if (deltaX >= 50)
			{
				deltaX = 0;
				this->_state = ERavenState::Stoping;
				return;
			}
			break;
		default:
			break;

		}
	}
	


}

// neu va cham voi vien gach thi chuyen qua stage moving 
void Ravens::Collision(list<GameObject*> obj, int dt)
{
	list<GameObject*>::iterator _itBegin;
	for (_itBegin = obj.begin(); _itBegin != obj.end(); _itBegin++)
	{
		float moveX;
		float moveY;
		float normalx;
		float normaly;
		GameObject* other = (*_itBegin);

		if (other->id == EnumID::Brick_ID)
		{

			Box box = this->GetBox();
			Box boxOther = other->GetBox();

			if (AABB(box, boxOther, moveX, moveY) == true)
			{
				//ERavenState::Stoping0;
			}
		}
	}
}


void Ravens::SetActive(float x, float y)
{

	if (active) return;
	if (abs(posX - x) <= 400 && abs(posY - y) <= 400)
	{

		if (posX - x > 0)
		{
			vX = -vX;
		}
		active = true;
	}
}